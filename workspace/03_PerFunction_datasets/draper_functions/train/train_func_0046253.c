canRealignStack(const MachineFunction &MF) const {
  const MachineFrameInfo *MFI = MF.getFrameInfo();


  return (RealignStack && (!MFI->hasVarSizedObjects() || EnableBasePointer));
}
