PerformANDCombine(SDNode *N,
                                 TargetLowering::DAGCombinerInfo &DCI) {


  SDValue Val = N->getOperand(0);
  SDValue Mask = N->getOperand(1);

  if (isa<ConstantSDNode>(Val)) {
    std::swap(Val, Mask);
  }

  SDValue AExt;

  if (Val.getOpcode() == ISD::ANY_EXTEND) {
    AExt = Val;
    Val = Val->getOperand(0);
  }

  if (Val->isMachineOpcode() && Val->getMachineOpcode() == NVPTX::IMOV16rr) {
    Val = Val->getOperand(0);
  }

  if (Val->getOpcode() == NVPTXISD::LoadV2 ||
      Val->getOpcode() == NVPTXISD::LoadV4) {
    ConstantSDNode *MaskCnst = dyn_cast<ConstantSDNode>(Mask);
    if (!MaskCnst) {

      return SDValue();
    }

    uint64_t MaskVal = MaskCnst->getZExtValue();
    if (MaskVal != 0xff) {

      return SDValue();
    }

    MemSDNode *Mem = dyn_cast<MemSDNode>(Val);
    if (!Mem) {

      return SDValue();
    }

    EVT MemVT = Mem->getMemoryVT();
    if (MemVT != MVT::v2i8 && MemVT != MVT::v4i8) {

      return SDValue();
    }

    unsigned ExtType =
      cast<ConstantSDNode>(Val->getOperand(Val->getNumOperands()-1))->
        getZExtValue();
    if (ExtType == ISD::SEXTLOAD) {


      return SDValue();
    }

    bool AddTo = false;
    if (AExt.getNode() != 0) {

      Val = DCI.DAG.getNode(ISD::ZERO_EXTEND, SDLoc(N),
                            AExt.getValueType(), Val);
      AddTo = true;
    }


    DCI.CombineTo(N, Val, AddTo);
  }

  return SDValue();
}
