resolveDependencies(ProgramSet* programSet)
    {
        Program* psProgram = programSet->getCpuFragmentProgram();
        Program* vsProgram = programSet->getCpuVertexProgram();
		psProgram->addDependency(FFP_LIB_TEXTURING);
        psProgram->addDependency("SGXLib_TriplanarTexturing");
        vsProgram->addDependency(FFP_LIB_COMMON);
        return true;
    }
