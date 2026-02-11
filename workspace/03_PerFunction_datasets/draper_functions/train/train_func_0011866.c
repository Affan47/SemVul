computeDataLayout(const Triple &TT) {
  if (TT.getArch() == Triple::bpfeb)
    return "E-m:e-p:64:64-i64:64-n32:64-S128";
  else
    return "e-m:e-p:64:64-i64:64-n32:64-S128";
}
