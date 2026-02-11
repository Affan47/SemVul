getNode(unsigned Opcode, DebugLoc DL, EVT VT) {
  FoldingSetNodeID ID;
  AddNodeIDNode(ID, Opcode, getVTList(VT), 0, 0);
  void *IP = 0;
  if (SDNode *E = CSEMap.FindNodeOrInsertPos(ID, IP))
    return SDValue(E, 0);

  SDNode *N = new (NodeAllocator) SDNode(Opcode, DL, getVTList(VT));
  CSEMap.InsertNode(N, IP);

  AllNodes.push_back(N);
#ifndef NDEBUG
  VerifySDNode(N);
#endif
  return SDValue(N, 0);
}
