getMatchingSuperReg(unsigned Reg, unsigned SubIdx,
                                             const MCRegisterClass *RC) const {
  for (MCSuperRegIterator Supers(Reg, this); Supers.isValid(); ++Supers)
    if (RC->contains(*Supers) && Reg == getSubReg(*Supers, SubIdx))
      return *Supers;
  return 0;
}
