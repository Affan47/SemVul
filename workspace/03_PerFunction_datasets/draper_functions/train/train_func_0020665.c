HasOtherRegSequenceUses(unsigned Reg, MachineInstr *RegSeq,
                                    MachineRegisterInfo *MRI) {
  for (MachineRegisterInfo::use_iterator UI = MRI->use_begin(Reg),
         UE = MRI->use_end(); UI != UE; ++UI) {
    MachineInstr *UseMI = &*UI;
    if (UseMI != RegSeq && UseMI->isRegSequence())
      return true;
  }
  return false;
}
