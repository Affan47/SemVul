IsOnlyNullComparedAndFreed(Value *V, SmallVectorImpl<WeakVH> &Users,
                                       int Depth = 0) {
  if (Depth == 8)
    return false;

  for (Value::use_iterator UI = V->use_begin(), UE = V->use_end();
       UI != UE; ++UI) {
    User *U = *UI;
    if (isFreeCall(U)) {
      Users.push_back(U);
      continue;
    }
    if (ICmpInst *ICI = dyn_cast<ICmpInst>(U)) {
      if (ICI->isEquality() && isa<ConstantPointerNull>(ICI->getOperand(1))) {
        Users.push_back(ICI);
        continue;
      }
    }
    if (BitCastInst *BCI = dyn_cast<BitCastInst>(U)) {
      if (IsOnlyNullComparedAndFreed(BCI, Users, Depth+1)) {
        Users.push_back(BCI);
        continue;
      }
    }
    if (GetElementPtrInst *GEPI = dyn_cast<GetElementPtrInst>(U)) {
      if (IsOnlyNullComparedAndFreed(GEPI, Users, Depth+1)) {
        Users.push_back(GEPI);
        continue;
      }
    }
    if (IntrinsicInst *II = dyn_cast<IntrinsicInst>(U)) {
      if (II->getIntrinsicID() == Intrinsic::lifetime_start ||
          II->getIntrinsicID() == Intrinsic::lifetime_end) {
        Users.push_back(II);
        continue;
      }
    }
    return false;
  }
  return true;
}
