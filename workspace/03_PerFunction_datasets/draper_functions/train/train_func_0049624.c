FeasibilityAnalysis(BBInfo &BBI,
                                      SmallVectorImpl<MachineOperand> &Pred,
                                      bool isTriangle, bool RevBranch) {

  if (BBI.IsDone || BBI.IsUnpredicable)
    return false;


  if (BBI.Predicate.size() && !TII->SubsumesPredicate(BBI.Predicate, Pred))
    return false;

  if (BBI.BrCond.size()) {
    if (!isTriangle)
      return false;


    SmallVector<MachineOperand, 4> RevPred(Pred.begin(), Pred.end());
    SmallVector<MachineOperand, 4> Cond(BBI.BrCond.begin(), BBI.BrCond.end());
    if (RevBranch) {
      if (TII->ReverseBranchCondition(Cond))
        return false;
    }
    if (TII->ReverseBranchCondition(RevPred) ||
        !TII->SubsumesPredicate(Cond, RevPred))
      return false;
  }

  return true;
}
