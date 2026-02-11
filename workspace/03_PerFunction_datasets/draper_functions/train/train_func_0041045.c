setFog(FogMode mode, const ColourValue& colour,
        Real expDensity, Real linearStart, Real linearEnd)
    {
        (void)mode;
        mFogColour = colour;
        mFogParams.x = expDensity;
        mFogParams.y = linearStart;
        mFogParams.z = linearEnd;
        mFogParams.w = linearEnd != linearStart ? 1 / (linearEnd - linearStart) : 0;
    }
