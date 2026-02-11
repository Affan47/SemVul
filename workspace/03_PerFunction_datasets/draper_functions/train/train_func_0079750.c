SelectAddrModeImm12(SDValue N,
                                          SDValue &Base,
                                          SDValue &OffImm) {


  if (N.getOpcode() != ISD::ADD && N.getOpcode() != ISD::SUB &&
      !CurDAG->isBaseWithConstantOffset(N)) {
    if (N.getOpcode() == ISD::FrameIndex) {

      int FI = cast<FrameIndexSDNode>(N)->getIndex();
      Base = CurDAG->getTargetFrameIndex(
          FI, TLI->getPointerTy(CurDAG->getDataLayout()));
      OffImm  = CurDAG->getTargetConstant(0, SDLoc(N), MVT::i32);
      return true;
    }

    if (N.getOpcode() == ARMISD::Wrapper &&
        N.getOperand(0).getOpcode() != ISD::TargetGlobalAddress) {
      Base = N.getOperand(0);
    } else
      Base = N;
    OffImm  = CurDAG->getTargetConstant(0, SDLoc(N), MVT::i32);
    return true;
  }

  if (ConstantSDNode *RHS = dyn_cast<ConstantSDNode>(N.getOperand(1))) {
    int RHSC = (int)RHS->getSExtValue();
    if (N.getOpcode() == ISD::SUB)
      RHSC = -RHSC;

    if (RHSC > -0x1000 && RHSC < 0x1000) {
      Base   = N.getOperand(0);
      if (Base.getOpcode() == ISD::FrameIndex) {
        int FI = cast<FrameIndexSDNode>(Base)->getIndex();
        Base = CurDAG->getTargetFrameIndex(
            FI, TLI->getPointerTy(CurDAG->getDataLayout()));
      }
      OffImm = CurDAG->getTargetConstant(RHSC, SDLoc(N), MVT::i32);
      return true;
    }
  }


  Base = N;
  OffImm  = CurDAG->getTargetConstant(0, SDLoc(N), MVT::i32);
  return true;
}
