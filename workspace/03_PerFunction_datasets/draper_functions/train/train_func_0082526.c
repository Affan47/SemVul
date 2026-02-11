getLoad(ISD::MemIndexedMode AM, ISD::LoadExtType ExtType,
                      EVT VT, DebugLoc dl, SDValue Chain,
                      SDValue Ptr, SDValue Offset,
                      const Value *SV, int SVOffset, EVT MemVT,
                      bool isVolatile, bool isNonTemporal,
                      unsigned Alignment) {
  if (Alignment == 0)
    Alignment = getEVTAlignment(VT);


  if (!SV)
    if (const FrameIndexSDNode *FI =
          dyn_cast<const FrameIndexSDNode>(Ptr.getNode()))
      SV = PseudoSourceValue::getFixedStack(FI->getIndex());

  MachineFunction &MF = getMachineFunction();
  unsigned Flags = MachineMemOperand::MOLoad;
  if (isVolatile)
    Flags |= MachineMemOperand::MOVolatile;
  if (isNonTemporal)
    Flags |= MachineMemOperand::MONonTemporal;
  MachineMemOperand *MMO =
    MF.getMachineMemOperand(SV, Flags, SVOffset,
                            MemVT.getStoreSize(), Alignment);
  return getLoad(AM, ExtType, VT, dl, Chain, Ptr, Offset, MemVT, MMO);
}
