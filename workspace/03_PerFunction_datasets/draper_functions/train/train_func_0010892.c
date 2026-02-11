createPPCMCRegisterInfo(const Triple &TT) {
  bool isPPC64 =
      (TT.getArch() == Triple::ppc64 || TT.getArch() == Triple::ppc64le);
  unsigned Flavour = isPPC64 ? 0 : 1;
  unsigned RA = isPPC64 ? PPC::LR8 : PPC::LR;

  MCRegisterInfo *X = new MCRegisterInfo();
  InitPPCMCRegisterInfo(X, RA, Flavour, Flavour);
  return X;
}
