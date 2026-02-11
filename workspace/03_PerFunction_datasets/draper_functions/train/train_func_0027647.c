setReg(unsigned Reg) {
  if (getReg() == Reg) return;


  if (MachineInstr *MI = getParent())
    if (MachineBasicBlock *MBB = MI->getParent())
      if (MachineFunction *MF = MBB->getParent()) {
        RemoveRegOperandFromRegInfo();
        SmallContents.RegNo = Reg;
        AddRegOperandToRegInfo(&MF->getRegInfo());
        return;
      }


  SmallContents.RegNo = Reg;
}
