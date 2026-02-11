removePassGroup(Pass* p)
    {
        PassGroupRenderableMap::iterator i;

        i = mGrouped.find(p);
        if (i != mGrouped.end())
        {

            OGRE_DELETE_T(i->second, RenderableList, MEMCATEGORY_SCENE_CONTROL);

            mGrouped.erase(i);
        }
    }
