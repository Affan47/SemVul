FoldOffsetIntoAddress(uint64_t Offset,
                                            X86ISelAddressMode &AM) {
  int64_t Val = AM.Disp + Offset;
  CodeModel::Model M = TM.getCodeModel();
  if (Subtarget->is64Bit()) {
    if (!X86::isOffsetSuitableForCodeModel(Val, M,
                                           AM.hasSymbolicDisplacement()))
      return true;


    if (AM.BaseType == X86ISelAddressMode::FrameIndexBase &&
        !isDispSafeForFrameIndex(Val))
      return true;
  }
  AM.Disp = Val;
  return false;

}
