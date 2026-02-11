createLowLevelImpl(void)
    {
        mAssemblerProgram = GpuProgramPtr(OGRE_NEW GLSLGpuProgram( this ));

        mAssemblerProgram->setAdjacencyInfoRequired(isAdjacencyInfoRequired());
    }
