setDualGridVisible(const bool visible)
    {
        mShared->dualGridVisible = visible;
        if (mChildren)
        {
            mChildren[0]->setDualGridVisible(visible);
            if (mChildren[1])
            {
                mChildren[1]->setDualGridVisible(visible);
                mChildren[2]->setDualGridVisible(visible);
                mChildren[3]->setDualGridVisible(visible);
                mChildren[4]->setDualGridVisible(visible);
                mChildren[5]->setDualGridVisible(visible);
                mChildren[6]->setDualGridVisible(visible);
                mChildren[7]->setDualGridVisible(visible);
            }
        }
    }
