resolveDependencies(ProgramSet* programSet)
{
    if (mFogMode == FOG_NONE)
        return true;

    Program* vsProgram = programSet->getCpuVertexProgram();
    Program* psProgram = programSet->getCpuFragmentProgram();

    vsProgram->addDependency(FFP_LIB_FOG);
    psProgram->addDependency(FFP_LIB_COMMON);

    psProgram->addDependency(FFP_LIB_FOG);
    psProgram->addDependency(FFP_LIB_TEXTURING);

    return true;
}
