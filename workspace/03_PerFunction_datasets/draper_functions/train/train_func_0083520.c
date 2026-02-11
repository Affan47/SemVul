isLeafProc(MachineFunction &MF) const
{

  MachineRegisterInfo &MRI = MF.getRegInfo();
  MachineFrameInfo    *MFI = MF.getFrameInfo();

  return !(MFI->hasCalls()
           || !MRI.reg_nodbg_empty(SP::L0)
           || !MRI.reg_nodbg_empty(SP::O6)
           || hasFP(MF));
}
