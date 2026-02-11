getSubRegs(unsigned Reg, BitVector &SRs) const {
  for (MCSubRegIterator I(Reg, HRI); I.isValid(); ++I)
    SRs[*I] = true;
}
