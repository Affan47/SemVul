getModRefInfo(const LoadInst *L, const Value *P, unsigned Size) {

  if (L->isVolatile())
    return ModRef;


  if (!alias(L->getOperand(0), getTypeStoreSize(L->getType()), P, Size))
    return NoModRef;


  return Ref;
}
