setWidth(Real width)
    {
        if (mMetricsMode != GMM_RELATIVE)
        {
            mPixelWidth = width;
        }
        else
        {
            mWidth = width;
        }
        mDerivedOutOfDate = true;
        _positionsOutOfDate();
    }
