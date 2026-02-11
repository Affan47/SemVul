addPSNormalFetchInvocation(Function* psMain, const int groupOrder, int& internalCounter)
{
    FunctionInvocation* curFuncInvocation = NULL;

	bool isHLSL = Ogre::RTShader::ShaderGenerator::getSingleton().getTargetLanguage() == "hlsl";

	if (isHLSL)
		FFPTexturing::AddTextureSampleWrapperInvocation(mNormalMapSampler, mNormalMapSamplerState, GCT_SAMPLER2D, psMain, groupOrder, internalCounter);

    curFuncInvocation = OGRE_NEW FunctionInvocation(SGX_FUNC_FETCHNORMAL, groupOrder, internalCounter++);

	if (isHLSL)
		curFuncInvocation->pushOperand(FFPTexturing::GetSamplerWrapperParam(mNormalMapSampler, psMain), Operand::OPS_IN);
	else
		curFuncInvocation->pushOperand(mNormalMapSampler, Operand::OPS_IN);

    curFuncInvocation->pushOperand(mPSInTexcoord, Operand::OPS_IN);
	curFuncInvocation->pushOperand(mPSNormal, Operand::OPS_OUT);
    psMain->addAtomInstance(curFuncInvocation);

    return true;
}
