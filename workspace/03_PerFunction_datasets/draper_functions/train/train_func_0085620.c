CreateRegs(const Type *Ty) {
  SmallVector<EVT, 4> ValueVTs;
  ComputeValueVTs(TLI, Ty, ValueVTs);

  unsigned FirstReg = 0;
  for (unsigned Value = 0, e = ValueVTs.size(); Value != e; ++Value) {
    EVT ValueVT = ValueVTs[Value];
    EVT RegisterVT = TLI.getRegisterType(Ty->getContext(), ValueVT);

    unsigned NumRegs = TLI.getNumRegisters(Ty->getContext(), ValueVT);
    for (unsigned i = 0; i != NumRegs; ++i) {
      unsigned R = CreateReg(RegisterVT);
      if (!FirstReg) FirstReg = R;
    }
  }
  return FirstReg;
}
