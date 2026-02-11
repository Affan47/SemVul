dominates(const DILocation *DL, MachineBasicBlock *MBB) {
  LexicalScope *Scope = getOrCreateLexicalScope(DL);
  if (!Scope)
    return false;


  if (Scope == CurrentFnLexicalScope && MBB->getParent() == MF)
    return true;

  bool Result = false;
  for (MachineBasicBlock::iterator I = MBB->begin(), E = MBB->end(); I != E;
       ++I) {
    if (const DILocation *IDL = I->getDebugLoc())
      if (LexicalScope *IScope = getOrCreateLexicalScope(IDL))
        if (Scope->dominates(IScope))
          return true;
  }
  return Result;
}
