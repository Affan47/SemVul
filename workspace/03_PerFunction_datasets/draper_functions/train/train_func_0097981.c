getIndexedType(const Type *Ptr, Value *Idx) {
  const PointerType *PTy = dyn_cast<PointerType>(Ptr);
  if (!PTy) return 0;


  if (!PTy->indexValid(Idx)) return 0;

  return PTy->getElementType();
}
