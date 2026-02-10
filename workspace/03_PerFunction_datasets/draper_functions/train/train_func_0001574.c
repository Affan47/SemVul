getStore(SDValue Chain, DebugLoc dl, SDValue Val,
                               SDValue Ptr, MachineMemOperand *MMO) {
  EVT VT = Val.getValueType();
  SDVTList VTs = getVTList(MVT::Other);
  SDValue Undef = getUNDEF(Ptr.getValueType());
  SDValue Ops[] = { Chain, Val, Ptr, Undef };
  FoldingSetNodeID ID;
  AddNodeIDNode(ID, ISD::STORE, VTs, Ops, 4);
  ID.AddInteger(VT.getRawBits());
  ID.AddInteger(encodeMemSDNodeFlags(false, ISD::UNINDEXED, MMO->isVolatile(),
                                     MMO->isNonTemporal()));
  void *IP = 0;
  if (SDNode *E = CSEMap.FindNodeOrInsertPos(ID, IP)) {
    cast<StoreSDNode>(E)->refineAlignment(MMO);
    return SDValue(E, 0);
  }
  SDNode *N = new (NodeAllocator) StoreSDNode(Ops, dl, VTs, ISD::UNINDEXED,
                                              false, VT, MMO);
  CSEMap.InsertNode(N, IP);
  AllNodes.push_back(N);
  return SDValue(N, 0);
}
