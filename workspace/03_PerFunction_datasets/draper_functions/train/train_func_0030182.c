UpdateRegAllocHint(unsigned Reg, unsigned NewReg,
                                        MachineFunction &MF) const {
  MachineRegisterInfo *MRI = &MF.getRegInfo();
  std::pair<unsigned, unsigned> Hint = MRI->getRegAllocationHint(Reg);
  if ((Hint.first == (unsigned)ARMRI::RegPairOdd ||
       Hint.first == (unsigned)ARMRI::RegPairEven) &&
      TargetRegisterInfo::isVirtualRegister(Hint.second)) {


    unsigned OtherReg = Hint.second;
    Hint = MRI->getRegAllocationHint(OtherReg);
    if (Hint.second == Reg)

      MRI->setRegAllocationHint(OtherReg, Hint.first, NewReg);
  }
}
