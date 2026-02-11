getCondCode(ISD::CondCode Cond) {
  if ((unsigned)Cond >= CondCodeNodes.size())
    CondCodeNodes.resize(Cond+1);

  if (CondCodeNodes[Cond] == 0) {
    CondCodeSDNode *N = new (NodeAllocator) CondCodeSDNode(Cond);
    CondCodeNodes[Cond] = N;
    AllNodes.push_back(N);
  }

  return SDValue(CondCodeNodes[Cond], 0);
}
