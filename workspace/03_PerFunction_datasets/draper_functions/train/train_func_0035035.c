addFunctionInvocations(ProgramSet* programSet)
{
    Program* vsProgram = programSet->getCpuVertexProgram();
    Function* vsMain = vsProgram->getEntryPointFunction();
    Program* psProgram = programSet->getCpuFragmentProgram();
    Function* psMain = psProgram->getEntryPointFunction();

    int internalCounter = 0;


    if (false == addVSInvocation(vsMain, FFP_VS_LIGHTING, internalCounter))
        return false;


    internalCounter = 0;


    if (false == addPSGlobalIlluminationInvocation(psMain, FFP_PS_COLOUR_BEGIN + 1, internalCounter))
        return false;


    for (unsigned int i=0; i < mLightParamsList.size(); ++i)
    {
        if (false == addPSIlluminationInvocation(&mLightParamsList[i], psMain, FFP_PS_COLOUR_BEGIN + 1, internalCounter))
            return false;
    }


    if (false == addPSFinalAssignmentInvocation(psMain, FFP_PS_COLOUR_BEGIN + 1, internalCounter))
        return false;


    return true;
}
