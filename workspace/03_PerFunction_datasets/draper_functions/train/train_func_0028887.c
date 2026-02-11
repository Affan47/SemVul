restoreCRs(bool isPPC64, bool is31,
           bool CR2Spilled, bool CR3Spilled, bool CR4Spilled,
           MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
           const std::vector<CalleeSavedInfo> &CSI, unsigned CSIIndex) {

  MachineFunction *MF = MBB.getParent();
  const PPCInstrInfo &TII = *MF->getSubtarget<PPCSubtarget>().getInstrInfo();
  DebugLoc DL;
  unsigned RestoreOp, MoveReg;

  if (isPPC64)

    return;
  else {

    MBB.insert(MI, addFrameReference(BuildMI(*MF, DL, TII.get(PPC::LWZ),
                                             PPC::R12),
                                     CSI[CSIIndex].getFrameIdx()));
    RestoreOp = PPC::MTOCRF;
    MoveReg = PPC::R12;
  }

  if (CR2Spilled)
    MBB.insert(MI, BuildMI(*MF, DL, TII.get(RestoreOp), PPC::CR2)
               .addReg(MoveReg, getKillRegState(!CR3Spilled && !CR4Spilled)));

  if (CR3Spilled)
    MBB.insert(MI, BuildMI(*MF, DL, TII.get(RestoreOp), PPC::CR3)
               .addReg(MoveReg, getKillRegState(!CR4Spilled)));

  if (CR4Spilled)
    MBB.insert(MI, BuildMI(*MF, DL, TII.get(RestoreOp), PPC::CR4)
               .addReg(MoveReg, getKillRegState(true)));
}
