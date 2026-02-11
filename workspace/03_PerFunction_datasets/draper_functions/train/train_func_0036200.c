emitInst(unsigned Opc, unsigned DstReg) {
    return BuildMI(*FuncInfo.MBB, FuncInfo.InsertPt, DbgLoc, TII.get(Opc),
                   DstReg);
  }
