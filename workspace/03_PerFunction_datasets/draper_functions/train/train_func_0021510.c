ShrinkDemandedConstant(SDValue Op,
                                                        const APInt &Demanded) {
  SDLoc dl(Op);


  switch (Op.getOpcode()) {
  default: break;
  case ISD::XOR:
  case ISD::AND:
  case ISD::OR: {
    ConstantSDNode *C = dyn_cast<ConstantSDNode>(Op.getOperand(1));
    if (!C) return false;

    if (Op.getOpcode() == ISD::XOR &&
        (C->getAPIntValue() | (~Demanded)).isAllOnesValue())
      return false;


    if (C->getAPIntValue().intersects(~Demanded)) {
      EVT VT = Op.getValueType();
      SDValue New = DAG.getNode(Op.getOpcode(), dl, VT, Op.getOperand(0),
                                DAG.getConstant(Demanded &
                                                C->getAPIntValue(),
                                                dl, VT));
      return CombineTo(Op, New);
    }

    break;
  }
  }

  return false;
}
