createAMDGPUMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitAMDGPUMCRegisterInfo(X, 0);
  return X;
}
