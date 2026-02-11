GetSmiConstant(Smi* source) {
  int value = source->value();
  if (value == 0) {
    xorl(kScratchRegister, kScratchRegister);
    return kScratchRegister;
  }
  if (value == 1) {
    return kSmiConstantRegister;
  }
  LoadSmiConstant(kScratchRegister, source);
  return kScratchRegister;
}
