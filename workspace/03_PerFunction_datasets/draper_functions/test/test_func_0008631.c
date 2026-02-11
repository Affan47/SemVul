NumRetVals(const Function *F) {
  if (F->getReturnType()->isVoidTy())
    return 0;
  else if (StructType *STy = dyn_cast<StructType>(F->getReturnType()))
    return STy->getNumElements();
  else
    return 1;
}
