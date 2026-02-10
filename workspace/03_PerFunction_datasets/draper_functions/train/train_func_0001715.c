FindCXAAtExit(Module &M) {
  Function *Fn = M.getFunction("__cxa_atexit");

  if (!Fn)
    return 0;

  FunctionType *FTy = Fn->getFunctionType();


  if (!FTy->getReturnType()->isIntegerTy() ||
      FTy->getNumParams() != 3 ||
      !FTy->getParamType(0)->isPointerTy() ||
      !FTy->getParamType(1)->isPointerTy() ||
      !FTy->getParamType(2)->isPointerTy())
    return 0;

  return Fn;
}
