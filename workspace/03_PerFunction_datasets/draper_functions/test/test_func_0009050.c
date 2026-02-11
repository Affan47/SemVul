isSafeMemAccess(uint64_t Offset, uint64_t MemSize,
                           Type *MemOpType, bool isStore,
                           AllocaInfo &Info, Instruction *TheAccess,
                           bool AllowWholeAccess) {
  const DataLayout &DL = TheAccess->getModule()->getDataLayout();

  if (Offset == 0 && AllowWholeAccess &&
      MemSize == DL.getTypeAllocSize(Info.AI->getAllocatedType())) {


    if (!MemOpType || MemOpType->isIntegerTy()) {
      if (isStore)
        Info.isMemCpyDst = true;
      else
        Info.isMemCpySrc = true;
      return;
    }


    if (isCompatibleAggregate(MemOpType, Info.AI->getAllocatedType())) {
      Info.hasSubelementAccess = true;
      return;
    }
  }

  Type *T = Info.AI->getAllocatedType();
  if (TypeHasComponent(T, Offset, MemSize, DL)) {
    Info.hasSubelementAccess = true;
    return;
  }

  return MarkUnsafe(Info, TheAccess);
}
