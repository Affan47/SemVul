setDebugDisplayEnabled(bool enabled, bool cascade)
    {
        ObjectMap::iterator oi, oiend;
        oiend = mObjectsByName.end();
        for (oi = mObjectsByName.begin(); oi != oiend; ++oi)
        {
            oi->second->setDebugDisplayEnabled(enabled);
        }

        if (cascade)
        {
            ChildNodeMap::iterator i, iend;
            iend = mChildren.end();
            for (i = mChildren.begin(); i != iend; ++i)
            {
                static_cast<SceneNode*>(i->second)->setDebugDisplayEnabled(enabled, cascade);
            }
        }
    }
