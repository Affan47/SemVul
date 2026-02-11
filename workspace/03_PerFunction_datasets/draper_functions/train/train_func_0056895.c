getFrameRegister(const MachineFunction &MF) const {
  const PPCFrameLowering *TFI = getFrameLowering(MF);

  if (!TM.isPPC64())
    return TFI->hasFP(MF) ? PPC::R31 : PPC::R1;
  else
    return TFI->hasFP(MF) ? PPC::X31 : PPC::X1;
}
