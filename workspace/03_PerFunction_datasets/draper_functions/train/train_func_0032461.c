getShadowPtrOffset(Value *Addr, IRBuilder<> &IRB) {
    Value *OffsetLong = IRB.CreatePointerCast(Addr, MS.IntptrTy);

    uint64_t AndMask = MS.MapParams->AndMask;
    if (AndMask)
      OffsetLong =
          IRB.CreateAnd(OffsetLong, ConstantInt::get(MS.IntptrTy, ~AndMask));

    uint64_t XorMask = MS.MapParams->XorMask;
    if (XorMask)
      OffsetLong =
          IRB.CreateXor(OffsetLong, ConstantInt::get(MS.IntptrTy, XorMask));
    return OffsetLong;
  }
