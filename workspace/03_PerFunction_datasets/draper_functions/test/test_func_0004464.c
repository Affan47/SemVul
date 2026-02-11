isSafeSROAElementUse(Value *V) {

  if (Constant *C = dyn_cast<Constant>(V))
    return isSafeToDestroyConstant(C);

  Instruction *I = dyn_cast<Instruction>(V);
  if (!I) return false;


  if (isa<LoadInst>(I)) return true;


  if (StoreInst *SI = dyn_cast<StoreInst>(I))
    return SI->getOperand(0) != V;


  GetElementPtrInst *GEPI = dyn_cast<GetElementPtrInst>(I);
  if (!GEPI) return false;

  if (GEPI->getNumOperands() < 3 || !isa<Constant>(GEPI->getOperand(1)) ||
      !cast<Constant>(GEPI->getOperand(1))->isNullValue())
    return false;

  for (User *U : GEPI->users())
    if (!isSafeSROAElementUse(U))
      return false;
  return true;
}
