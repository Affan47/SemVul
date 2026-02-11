setSpaceWidth( Real width )
    {
        mSpaceWidthOverridden = true;
        if (mMetricsMode != GMM_RELATIVE)
        {
            mPixelSpaceWidth = static_cast<unsigned short>(width);
        }
        else
        {
            mSpaceWidth = width;
        }

        mGeomPositionsOutOfDate = true;
    }
