
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_STUDIO_MAINWINDOW_PROJECT_INSTANCECOLLECTIONITEM_H
#define APPLESEED_STUDIO_MAINWINDOW_PROJECT_INSTANCECOLLECTIONITEM_H

// appleseed.studio headers.
#include "mainwindow/project/collectionitembase.h"
#include "mainwindow/project/itemregistry.h"
#include "mainwindow/project/projectbuilder.h"

// appleseed.foundation headers.
#include "foundation/platform/compiler.h"
#include "foundation/utility/uid.h"

// Standard headers.
#include <cassert>

// Forward declarations.
namespace appleseed { namespace studio { class ItemBase; } }
namespace appleseed { namespace studio { class ProjectBuilder; } }
class QString;

namespace appleseed {
namespace studio {

template <typename Entity, typename EntityItem, typename ParentEntity>
class InstanceCollectionItem
  : public CollectionItemBase<Entity>
{
  public:
    InstanceCollectionItem(
        const foundation::UniqueID  class_uid,
        const QString&              title,
        ParentEntity&               parent,
        ProjectBuilder&             project_builder);

  private:
    ParentEntity& m_parent;

    virtual ItemBase* create_item(Entity* entity) OVERRIDE;
};


//
// InstanceCollectionItem class implementation.
//

template <typename Entity, typename EntityItem, typename ParentEntity>
InstanceCollectionItem<Entity, EntityItem, ParentEntity>::InstanceCollectionItem(
    const foundation::UniqueID      class_uid,
    const QString&                  title,
    ParentEntity&                   parent,
    ProjectBuilder&                 project_builder)
  : CollectionItemBase<Entity>(class_uid, title, project_builder)
  , m_parent(parent)
{
}

template <typename Entity, typename EntityItem, typename ParentEntity>
ItemBase* InstanceCollectionItem<Entity, EntityItem, ParentEntity>::create_item(Entity* entity)
{
    assert(entity);

    ItemBase* item =
        new EntityItem(
            entity,
            m_parent,
            this,
            CollectionItemBase<Entity>::m_project_builder);

    CollectionItemBase<Entity>::m_project_builder.get_item_registry().insert(entity->get_uid(), item);

    return item;
}

}       // namespace studio
}       // namespace appleseed

#endif  // !APPLESEED_STUDIO_MAINWINDOW_PROJECT_INSTANCECOLLECTIONITEM_H
