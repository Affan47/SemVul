addPSFinalAssignmentInvocation( Function* psMain, const int groupOrder, int& internalCounter )
{
    FunctionInvocation* curFuncInvocation;

    curFuncInvocation = OGRE_NEW FunctionInvocation(FFP_FUNC_ASSIGN, FFP_PS_COLOUR_BEGIN + 1, internalCounter++);
    curFuncInvocation->pushOperand(mPSTempDiffuseColour, Operand::OPS_IN);
    curFuncInvocation->pushOperand(mPSDiffuse, Operand::OPS_OUT);
    psMain->addAtomInstance(curFuncInvocation);

    curFuncInvocation = OGRE_NEW FunctionInvocation(FFP_FUNC_ASSIGN, FFP_PS_COLOUR_BEGIN + 1, internalCounter++);
    curFuncInvocation->pushOperand(mPSDiffuse, Operand::OPS_IN);
    curFuncInvocation->pushOperand(mPSOutDiffuse, Operand::OPS_OUT);
    psMain->addAtomInstance(curFuncInvocation);

    if (mSpecularEnable)
    {
        curFuncInvocation = OGRE_NEW FunctionInvocation(FFP_FUNC_ASSIGN, FFP_PS_COLOUR_BEGIN + 1, internalCounter++);
        curFuncInvocation->pushOperand(mPSTempSpecularColour, Operand::OPS_IN);
        curFuncInvocation->pushOperand(mPSSpecular, Operand::OPS_OUT);
        psMain->addAtomInstance(curFuncInvocation);
    }

    return true;
}
