selectAddr16(
  SDNode *Parent, SDValue Addr, SDValue &Base, SDValue &Offset,
  SDValue &Alias) {
  SDLoc DL(Addr);
  EVT ValTy = Addr.getValueType();

  Alias = CurDAG->getTargetConstant(0, DL, ValTy);


  if (FrameIndexSDNode *FIN = dyn_cast<FrameIndexSDNode>(Addr)) {
    Base   = CurDAG->getTargetFrameIndex(FIN->getIndex(), ValTy);
    Offset = CurDAG->getTargetConstant(0, DL, ValTy);
    getMips16SPRefReg(Parent, Alias);
    return true;
  }

  if (Addr.getOpcode() == MipsISD::Wrapper) {
    Base   = Addr.getOperand(0);
    Offset = Addr.getOperand(1);
    return true;
  }
  if (TM.getRelocationModel() != Reloc::PIC_) {
    if ((Addr.getOpcode() == ISD::TargetExternalSymbol ||
        Addr.getOpcode() == ISD::TargetGlobalAddress))
      return false;
  }

  if (CurDAG->isBaseWithConstantOffset(Addr)) {
    ConstantSDNode *CN = dyn_cast<ConstantSDNode>(Addr.getOperand(1));
    if (isInt<16>(CN->getSExtValue())) {


      if (FrameIndexSDNode *FIN = dyn_cast<FrameIndexSDNode>
                                  (Addr.getOperand(0))) {
        Base = CurDAG->getTargetFrameIndex(FIN->getIndex(), ValTy);
        getMips16SPRefReg(Parent, Alias);
      }
      else
        Base = Addr.getOperand(0);

      Offset = CurDAG->getTargetConstant(CN->getZExtValue(), DL, ValTy);
      return true;
    }
  }

  if (Addr.getOpcode() == ISD::ADD) {


    if (Addr.getOperand(1).getOpcode() == MipsISD::Lo ||
        Addr.getOperand(1).getOpcode() == MipsISD::GPRel) {
      SDValue Opnd0 = Addr.getOperand(1).getOperand(0);
      if (isa<ConstantPoolSDNode>(Opnd0) || isa<GlobalAddressSDNode>(Opnd0) ||
          isa<JumpTableSDNode>(Opnd0)) {
        Base = Addr.getOperand(0);
        Offset = Opnd0;
        return true;
      }
    }


    const LSBaseSDNode *LS = dyn_cast<LSBaseSDNode>(Parent);

    if (LS) {
      if (LS->getMemoryVT() == MVT::f32 && Subtarget->hasMips4_32r2())
        return false;
      if (LS->getMemoryVT() == MVT::f64 && Subtarget->hasMips4_32r2())
        return false;
    }
  }
  Base   = Addr;
  Offset = CurDAG->getTargetConstant(0, DL, ValTy);
  return true;
}
