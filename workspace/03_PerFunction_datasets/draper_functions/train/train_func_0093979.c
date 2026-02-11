GetStringLength(Value *V) {
  if (!V->getType()->isPointerTy()) return 0;

  SmallPtrSet<PHINode*, 32> PHIs;
  uint64_t Len = GetStringLengthH(V, PHIs);


  return Len == ~0ULL ? 1 : Len;
}
