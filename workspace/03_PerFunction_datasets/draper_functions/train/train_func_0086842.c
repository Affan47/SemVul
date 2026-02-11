SelectAddrModePC(SDValue N,
                                       SDValue &Offset, SDValue &Label) {
  if (N.getOpcode() == ARMISD::PIC_ADD && N.hasOneUse()) {
    Offset = N.getOperand(0);
    SDValue N1 = N.getOperand(1);
    Label = CurDAG->getTargetConstant(cast<ConstantSDNode>(N1)->getZExtValue(),
                                      SDLoc(N), MVT::i32);
    return true;
  }

  return false;
}
