setCurrentLightList(const LightList* ll)
    {
        mCurrentLightList = ll;
        for(size_t i = 0; i < ll->size() && i < OGRE_MAX_SIMULTANEOUS_LIGHTS; ++i)
        {
            mSpotlightViewProjMatrixDirty[i] = true;
            mSpotlightWorldViewProjMatrixDirty[i] = true;
        }

    }
