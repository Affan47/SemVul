insertInstrBefore(
    MachineBasicBlock::iterator I, int NewOpcode) {
  MachineInstr *OldMI = &(*I);
  MachineBasicBlock *MBB = OldMI->getParent();
  MachineInstr *NewMBB =
      MBB->getParent()->CreateMachineInstr(TII->get(NewOpcode), DebugLoc());
  MBB->insert(I, NewMBB);

  SHOWNEWINSTR(NewMBB);
  return NewMBB;
}
