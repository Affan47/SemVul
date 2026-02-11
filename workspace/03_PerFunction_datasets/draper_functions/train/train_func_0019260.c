FindGlobalCtors(Module &M) {
  for (Module::global_iterator I = M.global_begin(), E = M.global_end();
       I != E; ++I)
    if (I->getName() == "llvm.global_ctors") {

      const ArrayType *ATy =dyn_cast<ArrayType>(I->getType()->getElementType());
      if (!ATy) return 0;
      const StructType *STy = dyn_cast<StructType>(ATy->getElementType());
      if (!STy || STy->getNumElements() != 2 ||
          !STy->getElementType(0)->isIntegerTy(32)) return 0;
      const PointerType *PFTy = dyn_cast<PointerType>(STy->getElementType(1));
      if (!PFTy) return 0;
      const FunctionType *FTy = dyn_cast<FunctionType>(PFTy->getElementType());
      if (!FTy || !FTy->getReturnType()->isVoidTy() ||
          FTy->isVarArg() || FTy->getNumParams() != 0)
        return 0;


      if (!I->hasDefinitiveInitializer()) return 0;
      ConstantArray *CA = dyn_cast<ConstantArray>(I->getInitializer());
      if (!CA) return 0;
      for (User::op_iterator i = CA->op_begin(), e = CA->op_end(); i != e; ++i)
        if (ConstantStruct *CS = dyn_cast<ConstantStruct>(*i)) {
          if (isa<ConstantPointerNull>(CS->getOperand(1)))
            continue;


          if (!isa<Function>(CS->getOperand(1)))
            return 0;


          ConstantInt *CI = dyn_cast<ConstantInt>(CS->getOperand(0));
          if (!CI || CI->getZExtValue() != 65535)
            return 0;
        } else {
          return 0;
        }

      return I;
    }
  return 0;
}
