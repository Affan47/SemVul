CallOptimizer(Function *Callee, CallInst *CI, IRBuilder<> &B) {

    FunctionType *FT = Callee->getFunctionType();
    if (FT->getNumParams() != 2 ||
        !FT->getReturnType()->isIntegerTy(32) ||
        FT->getParamType(0) != FT->getParamType(1) ||
        FT->getParamType(0) != B.getInt8PtrTy())
      return 0;

    Value *Str1P = CI->getArgOperand(0), *Str2P = CI->getArgOperand(1);
    if (Str1P == Str2P)
      return ConstantInt::get(CI->getType(), 0);

    std::string Str1, Str2;
    bool HasStr1 = GetConstantStringInfo(Str1P, Str1);
    bool HasStr2 = GetConstantStringInfo(Str2P, Str2);


    if (HasStr1 && HasStr2)
      return ConstantInt::get(CI->getType(),
                              StringRef(Str1).compare(Str2));

    if (HasStr1 && Str1.empty())
      return B.CreateNeg(B.CreateZExt(B.CreateLoad(Str2P, "strcmpload"),
                                      CI->getType()));

    if (HasStr2 && Str2.empty())
      return B.CreateZExt(B.CreateLoad(Str1P, "strcmpload"), CI->getType());


    uint64_t Len1 = GetStringLength(Str1P);
    uint64_t Len2 = GetStringLength(Str2P);
    if (Len1 && Len2) {

      if (!TD) return 0;

      return EmitMemCmp(Str1P, Str2P,
                        ConstantInt::get(TD->getIntPtrType(*Context),
                        std::min(Len1, Len2)), B, TD);
    }

    return 0;
  }
