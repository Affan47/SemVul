createStandardStrategies()
    {
        mGrid2DPageStrategy = OGRE_NEW Grid2DPageStrategy(this);
        addStrategy(mGrid2DPageStrategy);

        mGrid3DPageStrategy = OGRE_NEW Grid3DPageStrategy(this);
        addStrategy(mGrid3DPageStrategy);
    }
