dropAllReferences() {
  for (iterator I = begin(), E = end(); I != E; ++I)
    I->dropAllReferences();


  while (!BasicBlocks.empty())
    BasicBlocks.begin()->eraseFromParent();
}
