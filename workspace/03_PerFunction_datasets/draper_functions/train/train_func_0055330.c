ForgetSymbolicName(Instruction *PN, const SCEV *SymName) {
  SmallVector<Instruction *, 16> Worklist;
  PushDefUseChildren(PN, Worklist);

  SmallPtrSet<Instruction *, 8> Visited;
  Visited.insert(PN);
  while (!Worklist.empty()) {
    Instruction *I = Worklist.pop_back_val();
    if (!Visited.insert(I)) continue;

    ValueExprMapType::iterator It =
      ValueExprMap.find(static_cast<Value *>(I));
    if (It != ValueExprMap.end()) {


      if (It->second != SymName && !It->second->hasOperand(SymName))
        continue;


      if (!isa<PHINode>(I) ||
          !isa<SCEVUnknown>(It->second) ||
          (I != PN && It->second == SymName)) {
        ValuesAtScopes.erase(It->second);
        ValueExprMap.erase(It);
      }
    }

    PushDefUseChildren(I, Worklist);
  }
}
