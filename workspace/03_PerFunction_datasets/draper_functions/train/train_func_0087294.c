_findVisibleObjects(Camera* cam, RenderQueue* queue,
        VisibleObjectsBoundsInfo* visibleBounds, bool includeChildren,
        bool displayNodes, bool onlyShadowCasters)
    {

        if (!cam->isVisible(mWorldAABB))
            return;


        ObjectMap::iterator iobj;
        ObjectMap::iterator iobjend = mObjectsByName.end();
        for (iobj = mObjectsByName.begin(); iobj != iobjend; ++iobj)
        {
            MovableObject* mo = iobj->second;

            queue->processVisibleObject(mo, cam, onlyShadowCasters, visibleBounds);
        }

        if (includeChildren)
        {
            ChildNodeMap::iterator child, childend;
            childend = mChildren.end();
            for (child = mChildren.begin(); child != childend; ++child)
            {
                SceneNode* sceneChild = static_cast<SceneNode*>(child->second);
                sceneChild->_findVisibleObjects(cam, queue, visibleBounds, includeChildren,
                    displayNodes, onlyShadowCasters);
            }
        }

        if (displayNodes)
        {

            queue->addRenderable(getDebugRenderable());
        }


        if ( !mHideBoundingBox &&
             (mShowBoundingBox || (mCreator && mCreator->getShowBoundingBoxes())) )
        {
            _addBoundingBoxToQueue(queue);
        }


    }
