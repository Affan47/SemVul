_updateFromParent(void) const
    {
        updateFromParentImpl();


        if (mListener)
        {
            mListener->nodeUpdated(this);
        }
    }
