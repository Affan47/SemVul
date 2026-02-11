addGlobalIlluminationInvocation(Function* vsMain, const int groupOrder, int& internalCounter)
{
	FunctionInvocation* curFuncInvocation = NULL;

	if ((mTrackVertexColourType & TVC_AMBIENT) == 0 &&
		(mTrackVertexColourType & TVC_EMISSIVE) == 0)
	{
		curFuncInvocation = OGRE_NEW FunctionInvocation(FFP_FUNC_ASSIGN, groupOrder, internalCounter++);
		curFuncInvocation->pushOperand(mDerivedSceneColour, Operand::OPS_IN);
		curFuncInvocation->pushOperand(mVSOutDiffuse, Operand::OPS_OUT);
		vsMain->addAtomInstance(curFuncInvocation);
	}
	else
	{
		if (mTrackVertexColourType & TVC_AMBIENT)
		{
			curFuncInvocation = OGRE_NEW FunctionInvocation(FFP_FUNC_MODULATE, groupOrder, internalCounter++);
			curFuncInvocation->pushOperand(mLightAmbientColour, Operand::OPS_IN);
			curFuncInvocation->pushOperand(mVSDiffuse, Operand::OPS_IN);
			curFuncInvocation->pushOperand(mVSOutDiffuse, Operand::OPS_OUT);
			vsMain->addAtomInstance(curFuncInvocation);
		}
		else
		{
			curFuncInvocation = OGRE_NEW FunctionInvocation(FFP_FUNC_ASSIGN, groupOrder, internalCounter++);
			curFuncInvocation->pushOperand(mDerivedAmbientLightColour, Operand::OPS_IN, Operand::OPM_XYZ);
			curFuncInvocation->pushOperand(mVSOutDiffuse, Operand::OPS_OUT, Operand::OPM_XYZ);
			vsMain->addAtomInstance(curFuncInvocation);
		}

		if (mTrackVertexColourType & TVC_EMISSIVE)
		{
			curFuncInvocation = OGRE_NEW FunctionInvocation(FFP_FUNC_ADD, groupOrder, internalCounter++);
			curFuncInvocation->pushOperand(mVSDiffuse, Operand::OPS_IN);
			curFuncInvocation->pushOperand(mVSOutDiffuse, Operand::OPS_IN);
			curFuncInvocation->pushOperand(mVSOutDiffuse, Operand::OPS_OUT);
			vsMain->addAtomInstance(curFuncInvocation);
		}
		else
		{
			curFuncInvocation = OGRE_NEW FunctionInvocation(FFP_FUNC_ADD, groupOrder, internalCounter++);
			curFuncInvocation->pushOperand(mSurfaceEmissiveColour, Operand::OPS_IN);
			curFuncInvocation->pushOperand(mVSOutDiffuse, Operand::OPS_IN);
			curFuncInvocation->pushOperand(mVSOutDiffuse, Operand::OPS_OUT);
			vsMain->addAtomInstance(curFuncInvocation);
		}
	}

	return true;
}
