runOnMachineFunction(MachineFunction &MF) {
  DEBUG(dbgs() << "Machine Function\n"
               << "********** EXPANDING POST-RA PSEUDO INSTRS **********\n"
               << "********** Function: " << MF.getName() << '\n');
  TRI = MF.getSubtarget().getRegisterInfo();
  TII = MF.getSubtarget().getInstrInfo();

  bool MadeChange = false;

  for (MachineFunction::iterator mbbi = MF.begin(), mbbe = MF.end();
       mbbi != mbbe; ++mbbi) {
    for (MachineBasicBlock::iterator mi = mbbi->begin(), me = mbbi->end();
         mi != me;) {
      MachineInstr *MI = mi;

      ++mi;


      if (!MI->isPseudo())
        continue;


      if (TII->expandPostRAPseudo(MI)) {
        MadeChange = true;
        continue;
      }


      switch (MI->getOpcode()) {
      case TargetOpcode::SUBREG_TO_REG:
        MadeChange |= LowerSubregToReg(MI);
        break;
      case TargetOpcode::COPY:
        MadeChange |= LowerCopy(MI);
        break;
      case TargetOpcode::DBG_VALUE:
        continue;
      case TargetOpcode::INSERT_SUBREG:
      case TargetOpcode::EXTRACT_SUBREG:
        llvm_unreachable("Sub-register pseudos should have been eliminated.");
      }
    }
  }

  return MadeChange;
}
