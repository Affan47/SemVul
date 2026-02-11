updateDebugInfo(Instruction *Inst) const override {
    for (SmallVectorImpl<DbgDeclareInst *>::const_iterator I = DDIs.begin(),
           E = DDIs.end(); I != E; ++I) {
      DbgDeclareInst *DDI = *I;
      if (StoreInst *SI = dyn_cast<StoreInst>(Inst))
        ConvertDebugDeclareToDebugValue(DDI, SI, *DIB);
      else if (LoadInst *LI = dyn_cast<LoadInst>(Inst))
        ConvertDebugDeclareToDebugValue(DDI, LI, *DIB);
    }
    for (SmallVectorImpl<DbgValueInst *>::const_iterator I = DVIs.begin(),
           E = DVIs.end(); I != E; ++I) {
      DbgValueInst *DVI = *I;
      Value *Arg = nullptr;
      if (StoreInst *SI = dyn_cast<StoreInst>(Inst)) {


        if (ZExtInst *ZExt = dyn_cast<ZExtInst>(SI->getOperand(0)))
          Arg = dyn_cast<Argument>(ZExt->getOperand(0));
        if (SExtInst *SExt = dyn_cast<SExtInst>(SI->getOperand(0)))
          Arg = dyn_cast<Argument>(SExt->getOperand(0));
        if (!Arg)
          Arg = SI->getOperand(0);
      } else if (LoadInst *LI = dyn_cast<LoadInst>(Inst)) {
        Arg = LI->getOperand(0);
      } else {
        continue;
      }
      DIB->insertDbgValueIntrinsic(Arg, 0, DVI->getVariable(),
                                   DVI->getExpression(), DVI->getDebugLoc(),
                                   Inst);
    }
  }
