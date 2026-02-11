PropagateBackward(MachineBasicBlock::iterator MII,
                                          MachineBasicBlock *MBB,
                                          unsigned OldReg, unsigned NewReg) {
  if (MII == MBB->begin())
    return false;

  SmallVector<MachineOperand*, 4> Uses;
  SmallVector<MachineOperand*, 4> Refs;
  while (--MII != MBB->begin()) {
    bool FoundDef = false;

    Uses.clear();
    const MCInstrDesc &MCID = MII->getDesc();
    for (unsigned i = 0, e = MII->getNumOperands(); i != e; ++i) {
      MachineOperand &MO = MII->getOperand(i);
      if (!MO.isReg())
        continue;
      unsigned Reg = MO.getReg();
      if (Reg == 0)
        continue;
      if (Reg == OldReg) {
        if (MO.isImplicit())
          return false;


        if (MO.getSubReg() || MII->isSubregToReg())
          return false;

        const TargetRegisterClass *RC = TII->getRegClass(MCID, i, TRI);
        if (RC && !RC->contains(NewReg))
          return false;

        if (MO.isUse()) {
          Uses.push_back(&MO);
        } else {
          Refs.push_back(&MO);
          if (!MII->isRegTiedToUseOperand(i))
            FoundDef = true;
        }
      } else if (TRI->regsOverlap(Reg, NewReg)) {
        return false;
      } else if (TRI->regsOverlap(Reg, OldReg)) {
        if (!MO.isUse() || !MO.isKill())
          return false;
      }
    }

    if (FoundDef) {

      for (unsigned i = 0, e = Refs.size(); i != e; ++i)
        Refs[i]->setReg(NewReg);
      return true;
    }


    for (unsigned i = 0, e = Uses.size(); i != e; ++i)
      Refs.push_back(Uses[i]);
  }
  return false;
}
