OptimizeFixedFormatString(Function *Callee, CallInst *CI,
                                   IRBuilder<> &B) {

    std::string FormatStr;
    if (!GetConstantStringInfo(CI->getArgOperand(0), FormatStr))
      return 0;


    if (FormatStr.empty())
      return CI->use_empty() ? (Value*)CI :
                               ConstantInt::get(CI->getType(), 0);


    if (!CI->use_empty())
      return 0;


    if (FormatStr.size() == 1) {
      Value *Res = EmitPutChar(B.getInt32(FormatStr[0]), B, TD);
      if (CI->use_empty()) return CI;
      return B.CreateIntCast(Res, CI->getType(), true);
    }


    if (FormatStr[FormatStr.size()-1] == '\n' &&
        FormatStr.find('%') == std::string::npos) {


      FormatStr.erase(FormatStr.end()-1);
      Constant *C = ConstantArray::get(*Context, FormatStr, true);
      C = new GlobalVariable(*Callee->getParent(), C->getType(), true,
                             GlobalVariable::InternalLinkage, C, "str");
      EmitPutS(C, B, TD);
      return CI->use_empty() ? (Value*)CI :
                    ConstantInt::get(CI->getType(), FormatStr.size()+1);
    }


    if (FormatStr == "%c" && CI->getNumArgOperands() > 1 &&
        CI->getArgOperand(1)->getType()->isIntegerTy()) {
      Value *Res = EmitPutChar(CI->getArgOperand(1), B, TD);

      if (CI->use_empty()) return CI;
      return B.CreateIntCast(Res, CI->getType(), true);
    }


    if (FormatStr == "%s\n" && CI->getNumArgOperands() > 1 &&
        CI->getArgOperand(1)->getType()->isPointerTy()) {
      EmitPutS(CI->getArgOperand(1), B, TD);
      return CI;
    }
    return 0;
  }
