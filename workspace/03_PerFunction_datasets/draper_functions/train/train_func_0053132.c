RemapInstruction(Instruction *I,
                                    ValueToValueMapTy &VMap) {
  for (unsigned op = 0, E = I->getNumOperands(); op != E; ++op) {
    Value *Op = I->getOperand(op);
    ValueToValueMapTy::iterator It = VMap.find(Op);
    if (It != VMap.end())
      I->setOperand(op, It->second);
  }

  if (PHINode *PN = dyn_cast<PHINode>(I)) {
    for (unsigned i = 0, e = PN->getNumIncomingValues(); i != e; ++i) {
      ValueToValueMapTy::iterator It = VMap.find(PN->getIncomingBlock(i));
      if (It != VMap.end())
        PN->setIncomingBlock(i, cast<BasicBlock>(It->second));
    }
  }
}
