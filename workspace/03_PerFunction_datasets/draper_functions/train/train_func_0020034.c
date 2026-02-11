fastEmitInst_rri(unsigned MachineInstOpcode,
                                       const TargetRegisterClass *RC,
                                       unsigned Op0, bool Op0IsKill,
                                       unsigned Op1, bool Op1IsKill,
                                       uint64_t Imm) {
  unsigned ResultReg = createResultReg(RC);
  const MCInstrDesc &II = TII.get(MachineInstOpcode);


  Op0 = constrainOperandRegClass(II, Op0, 1);
  Op1 = constrainOperandRegClass(II, Op1, 2);
  if (II.getNumDefs() >= 1) {
    AddOptionalDefs(
        BuildMI(*FuncInfo.MBB, FuncInfo.InsertPt, DbgLoc, II, ResultReg)
            .addReg(Op0, Op0IsKill * RegState::Kill)
            .addReg(Op1, Op1IsKill * RegState::Kill)
            .addImm(Imm));
  } else {
    AddOptionalDefs(BuildMI(*FuncInfo.MBB, FuncInfo.InsertPt, DbgLoc, II)
                   .addReg(Op0, Op0IsKill * RegState::Kill)
                   .addReg(Op1, Op1IsKill * RegState::Kill)
                   .addImm(Imm));
    AddOptionalDefs(BuildMI(*FuncInfo.MBB, FuncInfo.InsertPt, DbgLoc,
                           TII.get(TargetOpcode::COPY), ResultReg)
                   .addReg(II.ImplicitDefs[0]));
  }
  return ResultReg;
}
