BuildCFI(MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator MBBI, DebugLoc DL,
                                MCCFIInstruction CFIInst) const {
  MachineFunction &MF = *MBB.getParent();
  unsigned CFIIndex = MF.getMMI().addFrameInst(CFIInst);
  BuildMI(MBB, MBBI, DL, TII.get(TargetOpcode::CFI_INSTRUCTION))
      .addCFIIndex(CFIIndex);
}
