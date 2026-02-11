CallOptimizer(Function *Callee, CallInst *CI, IRBuilder<> &B) {

    FunctionType *FT = Callee->getFunctionType();
    if (FT->getNumParams() != 2 ||
        FT->getReturnType() != B.getInt8PtrTy() ||
        FT->getParamType(0) != FT->getReturnType() ||
        !FT->getParamType(1)->isIntegerTy(32))
      return 0;

    Value *SrcStr = CI->getArgOperand(0);
    ConstantInt *CharC = dyn_cast<ConstantInt>(CI->getArgOperand(1));


    if (!CharC)
      return 0;

    std::string Str;
    if (!GetConstantStringInfo(SrcStr, Str)) {

      if (TD && CharC->isZero())
        return EmitStrChr(SrcStr, '\0', B, TD);
      return 0;
    }


    Str += '\0';


    size_t I = Str.rfind(CharC->getSExtValue());
    if (I == std::string::npos)
      return Constant::getNullValue(CI->getType());


    return B.CreateGEP(SrcStr, B.getInt64(I), "strrchr");
  }
