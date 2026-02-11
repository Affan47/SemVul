selectAddr(SDNode *Parent, SDValue N, SDValue &Base,
                                 SDValue &Scale, SDValue &Index,
                                 SDValue &Disp, SDValue &Segment) {
  X86ISelAddressMode AM;

  if (Parent &&


      Parent->getOpcode() != ISD::INTRINSIC_W_CHAIN &&
      Parent->getOpcode() != ISD::INTRINSIC_VOID &&
      Parent->getOpcode() != X86ISD::TLSCALL &&
      Parent->getOpcode() != X86ISD::EH_SJLJ_SETJMP &&
      Parent->getOpcode() != X86ISD::EH_SJLJ_LONGJMP) {
    unsigned AddrSpace =
      cast<MemSDNode>(Parent)->getPointerInfo().getAddrSpace();

    if (AddrSpace == 256)
      AM.Segment = CurDAG->getRegister(X86::GS, MVT::i16);
    if (AddrSpace == 257)
      AM.Segment = CurDAG->getRegister(X86::FS, MVT::i16);
  }

  if (matchAddress(N, AM))
    return false;

  MVT VT = N.getSimpleValueType();
  if (AM.BaseType == X86ISelAddressMode::RegBase) {
    if (!AM.Base_Reg.getNode())
      AM.Base_Reg = CurDAG->getRegister(0, VT);
  }

  if (!AM.IndexReg.getNode())
    AM.IndexReg = CurDAG->getRegister(0, VT);

  getAddressOperands(AM, SDLoc(N), Base, Scale, Index, Disp, Segment);
  return true;
}
