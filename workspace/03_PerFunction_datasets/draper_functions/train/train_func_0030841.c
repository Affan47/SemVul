detachAllObjectsFromBone(void)
    {
        detachAllObjectsImpl();


        if (mParentNode)
            mParentNode->needUpdate();
    }
