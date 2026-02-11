detachObject(MovableObject* obj)
    {
        ObjectMap::iterator i, iend;
        iend = mObjectsByName.end();
        for (i = mObjectsByName.begin(); i != iend; ++i)
        {
            if (i->second == obj)
            {
                mObjectsByName.erase(i);
                break;
            }
        }
        obj->_notifyAttached((SceneNode*)0);


        needUpdate();

    }
