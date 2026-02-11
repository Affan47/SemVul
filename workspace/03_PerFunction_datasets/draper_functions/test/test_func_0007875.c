CreateMemSet(Value *Ptr, Value *Val, Value *Size, unsigned Align,
             bool isVolatile, MDNode *TBAATag) {
  Ptr = getCastedInt8PtrValue(Ptr);
  Value *Ops[] = { Ptr, Val, Size, getInt32(Align), getInt1(isVolatile) };
  Type *Tys[] = { Ptr->getType(), Size->getType() };
  Module *M = BB->getParent()->getParent();
  Value *TheFn = Intrinsic::getDeclaration(M, Intrinsic::memset, Tys);

  CallInst *CI = createCallHelper(TheFn, Ops, this);


  if (TBAATag)
    CI->setMetadata(LLVMContext::MD_tbaa, TBAATag);

  return CI;
}
