CreateMemMove(Value *Dst, Value *Src, Value *Size, unsigned Align,
              bool isVolatile, MDNode *TBAATag) {
  Dst = getCastedInt8PtrValue(Dst);
  Src = getCastedInt8PtrValue(Src);

  Value *Ops[] = { Dst, Src, Size, getInt32(Align), getInt1(isVolatile) };
  Type *Tys[] = { Dst->getType(), Src->getType(), Size->getType() };
  Module *M = BB->getParent()->getParent();
  Value *TheFn = Intrinsic::getDeclaration(M, Intrinsic::memmove, Tys);

  CallInst *CI = createCallHelper(TheFn, Ops, this);


  if (TBAATag)
    CI->setMetadata(LLVMContext::MD_tbaa, TBAATag);

  return CI;
}
