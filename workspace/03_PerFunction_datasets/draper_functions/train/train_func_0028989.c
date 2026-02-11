forgetValue(Value *V) {
  Instruction *I = dyn_cast<Instruction>(V);
  if (!I) return;


  SmallVector<Instruction *, 16> Worklist;
  Worklist.push_back(I);

  SmallPtrSet<Instruction *, 8> Visited;
  while (!Worklist.empty()) {
    I = Worklist.pop_back_val();
    if (!Visited.insert(I)) continue;

    ValueExprMapType::iterator It = ValueExprMap.find(static_cast<Value *>(I));
    if (It != ValueExprMap.end()) {
      ValuesAtScopes.erase(It->second);
      ValueExprMap.erase(It);
      if (PHINode *PN = dyn_cast<PHINode>(I))
        ConstantEvolutionLoopExitValue.erase(PN);
    }

    PushDefUseChildren(I, Worklist);
  }
}
