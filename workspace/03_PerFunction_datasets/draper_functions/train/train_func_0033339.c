DuplicateInstruction(MachineInstr *MI,
                                     MachineBasicBlock *TailBB,
                                     MachineBasicBlock *PredBB,
                                     MachineFunction &MF,
                                     DenseMap<unsigned, unsigned> &LocalVRMap,
                                     const DenseSet<unsigned> &UsedByPhi) {
  MachineInstr *NewMI = TII->duplicate(MI, MF);
  for (unsigned i = 0, e = NewMI->getNumOperands(); i != e; ++i) {
    MachineOperand &MO = NewMI->getOperand(i);
    if (!MO.isReg())
      continue;
    unsigned Reg = MO.getReg();
    if (!TargetRegisterInfo::isVirtualRegister(Reg))
      continue;
    if (MO.isDef()) {
      const TargetRegisterClass *RC = MRI->getRegClass(Reg);
      unsigned NewReg = MRI->createVirtualRegister(RC);
      MO.setReg(NewReg);
      LocalVRMap.insert(std::make_pair(Reg, NewReg));
      if (isDefLiveOut(Reg, TailBB, MRI) || UsedByPhi.count(Reg))
        AddSSAUpdateEntry(Reg, NewReg, PredBB);
    } else {
      DenseMap<unsigned, unsigned>::iterator VI = LocalVRMap.find(Reg);
      if (VI != LocalVRMap.end()) {
        MO.setReg(VI->second);


        MO.setIsKill(false);
        MRI->constrainRegClass(VI->second, MRI->getRegClass(Reg));
      }
    }
  }
  PredBB->insert(PredBB->instr_end(), NewMI);
}
