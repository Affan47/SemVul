propagateThroughEdges(Function &F) {
  bool Changed = false;
  DEBUG(dbgs() << "\nPropagation through edges\n");
  for (const auto &BI : F) {
    const BasicBlock *BB = &BI;
    const BasicBlock *EC = EquivalenceClass[BB];


    for (unsigned i = 0; i < 2; i++) {
      uint64_t TotalWeight = 0;
      unsigned NumUnknownEdges = 0;
      Edge UnknownEdge, SelfReferentialEdge;

      if (i == 0) {

        for (auto *Pred : Predecessors[BB]) {
          Edge E = std::make_pair(Pred, BB);
          TotalWeight += visitEdge(E, &NumUnknownEdges, &UnknownEdge);
          if (E.first == E.second)
            SelfReferentialEdge = E;
        }
      } else {

        for (auto *Succ : Successors[BB]) {
          Edge E = std::make_pair(BB, Succ);
          TotalWeight += visitEdge(E, &NumUnknownEdges, &UnknownEdge);
        }
      }


      if (NumUnknownEdges <= 1) {
        uint64_t &BBWeight = BlockWeights[EC];
        if (NumUnknownEdges == 0) {


          if (TotalWeight > BBWeight) {
            BBWeight = TotalWeight;
            Changed = true;
            DEBUG(dbgs() << "All edge weights for " << BB->getName()
                         << " known. Set weight for block: ";
                  printBlockWeight(dbgs(), BB););
          }
          if (VisitedBlocks.insert(EC).second)
            Changed = true;
        } else if (NumUnknownEdges == 1 && VisitedBlocks.count(EC)) {


          if (BBWeight >= TotalWeight)
            EdgeWeights[UnknownEdge] = BBWeight - TotalWeight;
          else
            EdgeWeights[UnknownEdge] = 0;
          VisitedEdges.insert(UnknownEdge);
          Changed = true;
          DEBUG(dbgs() << "Set weight for edge: ";
                printEdgeWeight(dbgs(), UnknownEdge));
        }
      } else if (SelfReferentialEdge.first && VisitedBlocks.count(EC)) {
        uint64_t &BBWeight = BlockWeights[BB];

        if (BBWeight >= TotalWeight)
          EdgeWeights[SelfReferentialEdge] = BBWeight - TotalWeight;
        else
          EdgeWeights[SelfReferentialEdge] = 0;
        VisitedEdges.insert(SelfReferentialEdge);
        Changed = true;
        DEBUG(dbgs() << "Set self-referential edge weight to: ";
              printEdgeWeight(dbgs(), SelfReferentialEdge));
      }
    }
  }

  return Changed;
}
