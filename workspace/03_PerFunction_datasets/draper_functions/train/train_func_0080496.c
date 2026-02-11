InsertITInstructions(MachineBasicBlock &MBB) {
  bool Modified = false;

  SmallSet<unsigned, 4> Defs;
  SmallSet<unsigned, 4> Uses;
  MachineBasicBlock::iterator MBBI = MBB.begin(), E = MBB.end();
  while (MBBI != E) {
    MachineInstr *MI = &*MBBI;
    DebugLoc dl = MI->getDebugLoc();
    unsigned PredReg = 0;
    ARMCC::CondCodes CC = llvm::getITInstrPredicate(MI, PredReg);
    if (CC == ARMCC::AL) {
      ++MBBI;
      continue;
    }

    Defs.clear();
    Uses.clear();
    TrackDefUses(MI, Defs, Uses, TRI);


    MachineInstrBuilder MIB = BuildMI(MBB, MBBI, dl, TII->get(ARM::t2IT))
      .addImm(CC);


    MI->addOperand(MachineOperand::CreateReg(ARM::ITSTATE, false,
                                             true, false));

    MachineInstr *LastITMI = MI;
    MachineBasicBlock::iterator InsertPos = MIB;
    ++MBBI;


    ARMCC::CondCodes OCC = ARMCC::getOppositeCondition(CC);
    unsigned Mask = 0, Pos = 3;


    for (; MBBI != E && Pos &&
           (!MI->getDesc().isBranch() && !MI->getDesc().isReturn()) ; ++MBBI) {
      if (MBBI->isDebugValue())
        continue;

      MachineInstr *NMI = &*MBBI;
      MI = NMI;

      unsigned NPredReg = 0;
      ARMCC::CondCodes NCC = llvm::getITInstrPredicate(NMI, NPredReg);
      if (NCC == CC || NCC == OCC) {
        Mask |= (NCC & 1) << Pos;

        NMI->addOperand(MachineOperand::CreateReg(ARM::ITSTATE, false,
                                               true, false));
        LastITMI = NMI;
      } else {
        if (NCC == ARMCC::AL &&
            MoveCopyOutOfITBlock(NMI, CC, OCC, Defs, Uses)) {
          --MBBI;
          MBB.remove(NMI);
          MBB.insert(InsertPos, NMI);
          ++NumMovedInsts;
          continue;
        }
        break;
      }
      TrackDefUses(NMI, Defs, Uses, TRI);
      --Pos;
    }


    Mask |= (1 << Pos);

    Mask |= (CC & 1) << 4;
    MIB.addImm(Mask);


    LastITMI->findRegisterUseOperand(ARM::ITSTATE)->setIsKill();

    Modified = true;
    ++NumITs;
  }

  return Modified;
}
