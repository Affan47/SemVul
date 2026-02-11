canSpeculateInstrs(MachineBasicBlock *MBB) {


  if (!MBB->livein_empty()) {
    DEBUG(dbgs() << "BB#" << MBB->getNumber() << " has live-ins.\n");
    return false;
  }

  unsigned InstrCount = 0;


  for (MachineBasicBlock::iterator I = MBB->begin(),
       E = MBB->getFirstTerminator(); I != E; ++I) {
    if (I->isDebugValue())
      continue;

    if (++InstrCount > BlockInstrLimit && !Stress) {
      DEBUG(dbgs() << "BB#" << MBB->getNumber() << " has more than "
                   << BlockInstrLimit << " instructions.\n");
      return false;
    }


    if (I->isPHI()) {
      DEBUG(dbgs() << "Can't hoist: " << *I);
      return false;
    }


    if (I->mayLoad()) {
      DEBUG(dbgs() << "Won't speculate load: " << *I);
      return false;
    }


    bool DontMoveAcrossStore = true;
    if (!I->isSafeToMove(nullptr, DontMoveAcrossStore)) {
      DEBUG(dbgs() << "Can't speculate: " << *I);
      return false;
    }


    for (const MachineOperand &MO : I->operands()) {
      if (MO.isRegMask()) {
        DEBUG(dbgs() << "Won't speculate regmask: " << *I);
        return false;
      }
      if (!MO.isReg())
        continue;
      unsigned Reg = MO.getReg();


      if (MO.isDef() && TargetRegisterInfo::isPhysicalRegister(Reg))
        for (MCRegUnitIterator Units(Reg, TRI); Units.isValid(); ++Units)
          ClobberedRegUnits.set(*Units);

      if (!MO.readsReg() || !TargetRegisterInfo::isVirtualRegister(Reg))
        continue;
      MachineInstr *DefMI = MRI->getVRegDef(Reg);
      if (!DefMI || DefMI->getParent() != Head)
        continue;
      if (InsertAfter.insert(DefMI).second)
        DEBUG(dbgs() << "BB#" << MBB->getNumber() << " depends on " << *DefMI);
      if (DefMI->isTerminator()) {
        DEBUG(dbgs() << "Can't insert instructions below terminator.\n");
        return false;
      }
    }
  }
  return true;
}
