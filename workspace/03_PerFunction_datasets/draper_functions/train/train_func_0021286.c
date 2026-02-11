NumRetVals(const Function *F) {
  Type *RetTy = F->getReturnType();
  if (RetTy->isVoidTy())
    return 0;
  else if (StructType *STy = dyn_cast<StructType>(RetTy))
    return STy->getNumElements();
  else if (ArrayType *ATy = dyn_cast<ArrayType>(RetTy))
    return ATy->getNumElements();
  else
    return 1;
}
