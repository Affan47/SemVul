removeIfDead(MachineInstr *MI) {


  SmallVector<MachineInstr*, 1> DeadPhis;
  if (isDead(MI, DeadPhis)) {
    DEBUG(dbgs() << "HW looping will remove: " << *MI);


    for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
      const MachineOperand &MO = MI->getOperand(i);
      if (!MO.isReg() || !MO.isDef())
        continue;
      unsigned Reg = MO.getReg();
      MachineRegisterInfo::use_iterator nextI;
      for (MachineRegisterInfo::use_iterator I = MRI->use_begin(Reg),
           E = MRI->use_end(); I != E; I = nextI) {
        nextI = std::next(I);
        MachineOperand &Use = *I;
        MachineInstr *UseMI = I->getParent();
        if (UseMI == MI)
          continue;
        if (Use.isDebug())
          UseMI->getOperand(0).setReg(0U);
      }
    }

    MI->eraseFromParent();
    for (unsigned i = 0; i < DeadPhis.size(); ++i)
      DeadPhis[i]->eraseFromParent();
  }
}
