addKillFlags() {
  for (iterator I = begin(), E = end(); I != E; ++I) {
    unsigned Reg = I->first;
    if (TargetRegisterInfo::isPhysicalRegister(Reg))
      continue;
    if (mri_->reg_nodbg_empty(Reg))
      continue;
    LiveInterval *LI = I->second;


    for (LiveInterval::iterator RI = LI->begin(), RE = LI->end(); RI != RE;
         ++RI) {

      if (RI->end.isLoad())
        continue;
      MachineInstr *MI = getInstructionFromIndex(RI->end);
      if (!MI)
        continue;
      MI->addRegisterKilled(Reg, NULL);
    }
  }
}
