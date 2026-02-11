LowerSRXParts(SDValue Op, SelectionDAG &DAG) const {
  SDLoc DL(Op);
  EVT VT = Op.getValueType();

  SDValue Lo = Op.getOperand(0);
  SDValue Hi = Op.getOperand(1);
  SDValue Shift = Op.getOperand(2);
  SDValue Zero = DAG.getConstant(0, DL, VT);
  SDValue One  = DAG.getConstant(1, DL, VT);

  const bool SRA = Op.getOpcode() == ISD::SRA_PARTS;

  SDValue Width  = DAG.getConstant(VT.getSizeInBits(), DL, VT);
  SDValue Width1 = DAG.getConstant(VT.getSizeInBits() - 1, DL, VT);
  SDValue BigShift  = DAG.getNode(ISD::SUB, DL, VT, Shift, Width);
  SDValue CompShift = DAG.getNode(ISD::SUB, DL, VT, Width1, Shift);


  SDValue Overflow = DAG.getNode(ISD::SHL, DL, VT, Hi, CompShift);
  Overflow = DAG.getNode(ISD::SHL, DL, VT, Overflow, One);

  SDValue HiSmall = DAG.getNode(SRA ? ISD::SRA : ISD::SRL, DL, VT, Hi, Shift);
  SDValue LoSmall = DAG.getNode(ISD::SRL, DL, VT, Lo, Shift);
  LoSmall = DAG.getNode(ISD::OR, DL, VT, LoSmall, Overflow);

  SDValue LoBig = DAG.getNode(SRA ? ISD::SRA : ISD::SRL, DL, VT, Hi, BigShift);
  SDValue HiBig = SRA ? DAG.getNode(ISD::SRA, DL, VT, Hi, Width1) : Zero;

  Hi = DAG.getSelectCC(DL, Shift, Width, HiSmall, HiBig, ISD::SETULT);
  Lo = DAG.getSelectCC(DL, Shift, Width, LoSmall, LoBig, ISD::SETULT);

  return DAG.getNode(ISD::MERGE_VALUES, DL, DAG.getVTList(VT,VT), Lo, Hi);
}
