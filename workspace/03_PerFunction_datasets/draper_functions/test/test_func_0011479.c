_update(bool updateChildren, bool parentHasChanged)
    {
        bool checkMovables = false;

        if (mNeedParentUpdate || parentHasChanged)
        {

            checkMovables = true;
        }


        SceneNode::_update(updateChildren, parentHasChanged);

        if (checkMovables)
        {

            ObjectMap::const_iterator it, itend;
            itend = mObjectsByName.end();
            for (it = mObjectsByName.begin(); it != itend; ++it)
            {
                MovableObject* mov = it->second;

                static_cast<BspSceneManager*>(mCreator)->_notifyObjectMoved(
                    mov, this->_getDerivedPosition());

            }
        }

    }
