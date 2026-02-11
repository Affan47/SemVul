buildGraphFrom(CFLAAResult &Analysis, Function *Fn,
                           SmallVectorImpl<Value *> &ReturnedValues,
                           NodeMapT &Map, GraphT &Graph) {
  for (auto &Bb : Fn->getBasicBlockList())
    for (auto &Inst : Bb.getInstList())
      addInstructionToGraph(Analysis, Inst, ReturnedValues, Map, Graph);
}
