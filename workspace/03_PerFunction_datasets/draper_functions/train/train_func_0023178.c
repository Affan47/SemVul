PreprocessISelDAG() {
  SelectionDAG &DAG = *CurDAG;
  std::vector<SDNode*> Nodes;
  for (SDNode &Node : DAG.allnodes())
    Nodes.push_back(&Node);


  for (auto I: Nodes) {
    if (I->getOpcode() != ISD::OR)
      continue;

    auto IsZero = [] (const SDValue &V) -> bool {
      if (ConstantSDNode *SC = dyn_cast<ConstantSDNode>(V.getNode()))
        return SC->isNullValue();
      return false;
    };
    auto IsSelect0 = [IsZero] (const SDValue &Op) -> bool {
      if (Op.getOpcode() != ISD::SELECT)
        return false;
      return IsZero(Op.getOperand(1))  || IsZero(Op.getOperand(2));
    };

    SDValue N0 = I->getOperand(0), N1 = I->getOperand(1);
    EVT VT = I->getValueType(0);
    bool SelN0 = IsSelect0(N0);
    SDValue SOp = SelN0 ? N0 : N1;
    SDValue VOp = SelN0 ? N1 : N0;

    if (SOp.getOpcode() == ISD::SELECT && SOp.getNode()->hasOneUse()) {
      SDValue SC = SOp.getOperand(0);
      SDValue SX = SOp.getOperand(1);
      SDValue SY = SOp.getOperand(2);
      SDLoc DLS = SOp;
      if (IsZero(SY)) {
        SDValue NewOr = DAG.getNode(ISD::OR, DLS, VT, SX, VOp);
        SDValue NewSel = DAG.getNode(ISD::SELECT, DLS, VT, SC, NewOr, VOp);
        DAG.ReplaceAllUsesWith(I, NewSel.getNode());
      } else if (IsZero(SX)) {
        SDValue NewOr = DAG.getNode(ISD::OR, DLS, VT, SY, VOp);
        SDValue NewSel = DAG.getNode(ISD::SELECT, DLS, VT, SC, VOp, NewOr);
        DAG.ReplaceAllUsesWith(I, NewSel.getNode());
      }
    }
  }
}
