isPredReg(unsigned R) {
  if (!TargetRegisterInfo::isVirtualRegister(R))
    return false;
  const TargetRegisterClass *RC = MRI->getRegClass(R);
  return RC == &Hexagon::PredRegsRegClass;
}
