indexValid(const Value *V) const {

  if (V->getType()->isIntegerTy(32))
    if (const ConstantInt *CU = dyn_cast<ConstantInt>(V))
      return indexValid(CU->getZExtValue());
  return false;
}
