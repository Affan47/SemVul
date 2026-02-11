splitBlock(const BasicBlock *Old,
                                                   const BasicBlock* New) {
  const Function *F = Old->getParent();
  std::map<const Function*, EdgeWeights>::iterator J =
    EdgeInformation.find(F);
  if (J == EdgeInformation.end()) return;

  DEBUG(dbgs() << "Splitting " << Old->getName() << " to " << New->getName() << "\n");

  std::set<Edge> Edges;
  for (EdgeWeights::iterator ewi = J->second.begin(), ewe = J->second.end();
       ewi != ewe; ++ewi) {
    Edge old = ewi->first;
    if (old.first == Old) {
      Edges.insert(old);
    }
  }
  for (std::set<Edge>::iterator EI = Edges.begin(), EE = Edges.end();
       EI != EE; ++EI) {
    Edge newedge = getEdge(New, EI->second);
    replaceEdge(*EI, newedge);
  }

  double w = getExecutionCount(Old);
  setEdgeWeight(getEdge(Old, New), w);
  setExecutionCount(New, w);
}
