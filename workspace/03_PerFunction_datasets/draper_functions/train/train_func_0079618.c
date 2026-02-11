getNode(unsigned Opcode, DebugLoc DL, EVT VT,
                              const SDUse *Ops, unsigned NumOps) {
  switch (NumOps) {
  case 0: return getNode(Opcode, DL, VT);
  case 1: return getNode(Opcode, DL, VT, Ops[0]);
  case 2: return getNode(Opcode, DL, VT, Ops[0], Ops[1]);
  case 3: return getNode(Opcode, DL, VT, Ops[0], Ops[1], Ops[2]);
  default: break;
  }


  SmallVector<SDValue, 8> NewOps(Ops, Ops + NumOps);
  return getNode(Opcode, DL, VT, &NewOps[0], NumOps);
}
