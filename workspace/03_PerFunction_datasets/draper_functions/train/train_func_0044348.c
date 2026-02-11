_notifyResourceCreated(ResourcePtr& res)
    {
        if (mCurrentGroup && res->getGroup() == mCurrentGroup->name)
        {

            addCreatedResource(res, *mCurrentGroup);
        }
        else
        {

            ResourceGroup* grp = getResourceGroup(res->getGroup());
            if (grp)
            {
                addCreatedResource(res, *grp);
            }
        }

        fireResourceCreated(res);
    }
