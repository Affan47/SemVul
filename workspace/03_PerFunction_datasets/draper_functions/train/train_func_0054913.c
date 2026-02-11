getPointExtrusionDistance(const Light* l) const
    {
        if (mParentNode)
        {
            return getExtrusionDistance(mParentNode->_getDerivedPosition(), l);
        }
        else
        {
            return 0;
        }
    }
