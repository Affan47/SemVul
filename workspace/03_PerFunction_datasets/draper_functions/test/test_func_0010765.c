resolveDependencies(ProgramSet* programSet)
{
    Program* vsProgram = programSet->getCpuVertexProgram();
    vsProgram->addDependency(FFP_LIB_COMMON);
    vsProgram->addDependency(FFP_LIB_TRANSFORM);

    return true;
}
