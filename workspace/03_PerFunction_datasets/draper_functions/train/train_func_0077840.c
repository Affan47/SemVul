getSquaredViewDepth(const Camera* cam) const
    {
        const Region *region = mParent->getParent()->getParent();
        if (cam == region->mCamera)
            return region->mSquaredViewDepth;
        else
            return region->getParentNode()->getSquaredViewDepth(cam->getLodCamera());
    }
