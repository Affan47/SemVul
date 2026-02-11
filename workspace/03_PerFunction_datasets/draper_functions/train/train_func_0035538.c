createFPSpillSlot(MachineFunction &MF) {
  if (FPSpillSlotSet) {
    return FPSpillSlot;
  }
  const TargetRegisterClass *RC = &XCore::GRRegsRegClass;
  MachineFrameInfo *MFI = MF.getFrameInfo();
  FPSpillSlot = MFI->CreateStackObject(RC->getSize(), RC->getAlignment(), true);
  FPSpillSlotSet = true;
  return FPSpillSlot;
}
