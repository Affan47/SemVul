GetReturnInfo(const Type* ReturnType, Attributes attr,
                         SmallVectorImpl<ISD::OutputArg> &Outs,
                         const TargetLowering &TLI,
                         SmallVectorImpl<uint64_t> *Offsets) {
  SmallVector<EVT, 4> ValueVTs;
  ComputeValueVTs(TLI, ReturnType, ValueVTs);
  unsigned NumValues = ValueVTs.size();
  if (NumValues == 0) return;
  unsigned Offset = 0;

  for (unsigned j = 0, f = NumValues; j != f; ++j) {
    EVT VT = ValueVTs[j];
    ISD::NodeType ExtendKind = ISD::ANY_EXTEND;

    if (attr & Attribute::SExt)
      ExtendKind = ISD::SIGN_EXTEND;
    else if (attr & Attribute::ZExt)
      ExtendKind = ISD::ZERO_EXTEND;


    if (ExtendKind != ISD::ANY_EXTEND && VT.isInteger()) {
      EVT MinVT = TLI.getRegisterType(ReturnType->getContext(), MVT::i32);
      if (VT.bitsLT(MinVT))
        VT = MinVT;
    }

    unsigned NumParts = TLI.getNumRegisters(ReturnType->getContext(), VT);
    EVT PartVT = TLI.getRegisterType(ReturnType->getContext(), VT);
    unsigned PartSize = TLI.getTargetData()->getTypeAllocSize(
                        PartVT.getTypeForEVT(ReturnType->getContext()));


    ISD::ArgFlagsTy Flags = ISD::ArgFlagsTy();
    if (attr & Attribute::InReg)
      Flags.setInReg();


    if (attr & Attribute::SExt)
      Flags.setSExt();
    else if (attr & Attribute::ZExt)
      Flags.setZExt();

    for (unsigned i = 0; i < NumParts; ++i) {
      Outs.push_back(ISD::OutputArg(Flags, PartVT, true));
      if (Offsets) {
        Offsets->push_back(Offset);
        Offset += PartSize;
      }
    }
  }
}
