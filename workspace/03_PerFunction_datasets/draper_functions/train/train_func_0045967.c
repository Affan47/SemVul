visitCmpInst(CmpInst &I) {
  LatticeVal V1State = getValueState(I.getOperand(0));
  LatticeVal V2State = getValueState(I.getOperand(1));

  LatticeVal &IV = ValueState[&I];
  if (IV.isOverdefined()) return;

  if (V1State.isConstant() && V2State.isConstant())
    return markConstant(IV, &I, ConstantExpr::getCompare(I.getPredicate(),
                                                         V1State.getConstant(),
                                                        V2State.getConstant()));


  if (!V1State.isOverdefined() && !V2State.isOverdefined())
    return;


  if (PHINode *PN1 = dyn_cast<PHINode>(I.getOperand(0)))
    if (PHINode *PN2 = dyn_cast<PHINode>(I.getOperand(1)))
      if (PN1->getParent() == PN2->getParent()) {


        LatticeVal Result;
        for (unsigned i = 0, e = PN1->getNumIncomingValues(); i != e; ++i) {
          LatticeVal In1 = getValueState(PN1->getIncomingValue(i));
          BasicBlock *InBlock = PN1->getIncomingBlock(i);
          LatticeVal In2 =getValueState(PN2->getIncomingValueForBlock(InBlock));

          if (In1.isOverdefined() || In2.isOverdefined()) {
            Result.markOverdefined();
            break;
          }

          if (In1.isConstant() && In2.isConstant()) {
            Constant *V = ConstantExpr::getCompare(I.getPredicate(),
                                                   In1.getConstant(),
                                                   In2.getConstant());
            if (Result.isUndefined())
              Result.markConstant(V);
            else if (Result.isConstant() && Result.getConstant() != V) {
              Result.markOverdefined();
              break;
            }
          }
        }


        if (Result.isConstant()) {
          markConstant(&I, Result.getConstant());


          UsersOfOverdefinedPHIs.insert(std::make_pair(PN1, &I));
          UsersOfOverdefinedPHIs.insert(std::make_pair(PN2, &I));
          return;
        }

        if (Result.isUndefined())
          return;


        RemoveFromOverdefinedPHIs(&I, PN1);
        RemoveFromOverdefinedPHIs(&I, PN2);
      }

  markOverdefined(&I);
}
