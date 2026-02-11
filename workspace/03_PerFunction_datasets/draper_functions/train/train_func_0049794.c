fastLowerCall(CallLoweringInfo &CLI) {
  if (!TargetSupported)
    return false;

  CallingConv::ID CC = CLI.CallConv;
  bool IsTailCall = CLI.IsTailCall;
  bool IsVarArg = CLI.IsVarArg;
  const Value *Callee = CLI.Callee;
  MCSymbol *Symbol = CLI.Symbol;


  if (CC == CallingConv::Fast)
    return false;


  if (IsTailCall)
    return false;


  if (IsVarArg)
    return false;


  MVT RetVT;
  if (CLI.RetTy->isVoidTy())
    RetVT = MVT::isVoid;
  else if (!isTypeSupported(CLI.RetTy, RetVT))
    return false;

  for (auto Flag : CLI.OutFlags)
    if (Flag.isInReg() || Flag.isSRet() || Flag.isNest() || Flag.isByVal())
      return false;


  SmallVector<MVT, 16> OutVTs;
  OutVTs.reserve(CLI.OutVals.size());

  for (auto *Val : CLI.OutVals) {
    MVT VT;
    if (!isTypeLegal(Val->getType(), VT) &&
        !(VT == MVT::i1 || VT == MVT::i8 || VT == MVT::i16))
      return false;


    if (VT.isVector() || VT.getSizeInBits() > 64)
      return false;

    OutVTs.push_back(VT);
  }

  Address Addr;
  if (!computeCallAddress(Callee, Addr))
    return false;


  unsigned NumBytes;
  if (!processCallArgs(CLI, OutVTs, NumBytes))
    return false;

  if (!Addr.getGlobalValue())
    return false;


  unsigned DestAddress;
  if (Symbol)
    DestAddress = materializeExternalCallSym(Symbol);
  else
    DestAddress = materializeGV(Addr.getGlobalValue(), MVT::i32);
  emitInst(TargetOpcode::COPY, Mips::T9).addReg(DestAddress);
  MachineInstrBuilder MIB =
      BuildMI(*FuncInfo.MBB, FuncInfo.InsertPt, DbgLoc, TII.get(Mips::JALR),
              Mips::RA).addReg(Mips::T9);


  for (auto Reg : CLI.OutRegs)
    MIB.addReg(Reg, RegState::Implicit);


  MIB.addRegMask(TRI.getCallPreservedMask(*FuncInfo.MF, CC));

  CLI.Call = MIB;


  return finishCall(CLI, RetVT, NumBytes);
}
