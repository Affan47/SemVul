UpdateCallGraphAfterInlining(CallSite CS,
                                         Function::iterator FirstNewBlock,
                                         ValueToValueMapTy &VMap,
                                         InlineFunctionInfo &IFI) {
  CallGraph &CG = *IFI.CG;
  const Function *Caller = CS.getInstruction()->getParent()->getParent();
  const Function *Callee = CS.getCalledFunction();
  CallGraphNode *CalleeNode = CG[Callee];
  CallGraphNode *CallerNode = CG[Caller];


  CallGraphNode::iterator I = CalleeNode->begin(), E = CalleeNode->end();


  CallGraphNode::CalledFunctionsVector CallCache;
  if (CalleeNode == CallerNode) {
    CallCache.assign(I, E);
    I = CallCache.begin();
    E = CallCache.end();
  }

  for (; I != E; ++I) {
    const Value *OrigCall = I->first;

    ValueToValueMapTy::iterator VMI = VMap.find(OrigCall);

    if (VMI == VMap.end() || VMI->second == 0)
      continue;


    Instruction *NewCall = dyn_cast<Instruction>(VMI->second);
    if (NewCall == 0) continue;


    IFI.InlinedCalls.push_back(NewCall);


    if (I->second->getFunction() == 0)
      if (Function *F = CallSite(NewCall).getCalledFunction()) {

        CallerNode->addCalledFunction(CallSite(NewCall), CG[F]);

        continue;
      }

    CallerNode->addCalledFunction(CallSite(NewCall), I->second);
  }


  CallerNode->removeCallEdgeFor(CS);
}
