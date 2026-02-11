simplifyAddress(Address &Addr) {
  if (!isInt<16>(Addr.getOffset())) {
    unsigned TempReg =
        materialize32BitInt(Addr.getOffset(), &Mips::GPR32RegClass);
    unsigned DestReg = createResultReg(&Mips::GPR32RegClass);
    emitInst(Mips::ADDu, DestReg).addReg(TempReg).addReg(Addr.getReg());
    Addr.setReg(DestReg);
    Addr.setOffset(0);
  }
}
