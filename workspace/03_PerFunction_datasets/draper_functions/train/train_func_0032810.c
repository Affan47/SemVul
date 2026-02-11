runOnRegion(Region *R, RGPassManager &RGM) {
  if (R->isTopLevelRegion())
    return false;

  Func = R->getEntry()->getParent();
  ParentRegion = R;

  DT = &getAnalysis<DominatorTreeWrapperPass>().getDomTree();
  LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();

  orderNodes();
  collectInfos();
  createFlow();
  insertConditions(false);
  insertConditions(true);
  setPhiValues();
  rebuildSSA();


  Order.clear();
  Visited.clear();
  DeletedPhis.clear();
  AddedPhis.clear();
  Predicates.clear();
  Conditions.clear();
  Loops.clear();
  LoopPreds.clear();
  LoopConds.clear();

  return true;
}
