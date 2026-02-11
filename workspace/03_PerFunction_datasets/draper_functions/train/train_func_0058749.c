getProgram(GpuProgramUsage* const* gpuProgramUsage) const
    {
        OGRE_LOCK_MUTEX(mGpuProgramChangeMutex);
        OgreAssert(*gpuProgramUsage, "check whether program is available using hasGpuProgram()");
        return (*gpuProgramUsage)->getProgram();
    }
