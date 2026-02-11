splitReturnBlocks() {
  for (SetVector<BasicBlock*>::iterator I = BlocksToExtract.begin(),
         E = BlocksToExtract.end(); I != E; ++I)
    if (ReturnInst *RI = dyn_cast<ReturnInst>((*I)->getTerminator())) {
      BasicBlock *New = (*I)->splitBasicBlock(RI, (*I)->getName()+".ret");
      if (DT) {


        DomTreeNode *OldNode = DT->getNode(*I);
        SmallVector<DomTreeNode*, 8> Children;
        for (DomTreeNode::iterator DI = OldNode->begin(), DE = OldNode->end();
             DI != DE; ++DI)
          Children.push_back(*DI);

        DomTreeNode *NewNode = DT->addNewBlock(New, *I);

        for (SmallVector<DomTreeNode*, 8>::iterator I = Children.begin(),
               E = Children.end(); I != E; ++I)
          DT->changeImmediateDominator(*I, NewNode);
      }
    }
}
