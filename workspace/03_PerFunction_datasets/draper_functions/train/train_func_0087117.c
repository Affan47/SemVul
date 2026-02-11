getTextureFiltering(FilterType ft) const
    {

        switch (ft)
        {
        case FT_MIN:
            return mIsDefaultFiltering ?
                MaterialManager::getSingleton().getDefaultTextureFiltering(FT_MIN) : mMinFilter;
        case FT_MAG:
            return mIsDefaultFiltering ?
                MaterialManager::getSingleton().getDefaultTextureFiltering(FT_MAG) : mMagFilter;
        case FT_MIP:
            return mIsDefaultFiltering ?
                MaterialManager::getSingleton().getDefaultTextureFiltering(FT_MIP) : mMipFilter;
        }

        return mMinFilter;
    }
