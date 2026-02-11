AddBlockAndPredsToSet(BasicBlock *InputBB, BasicBlock *StopBlock,
                                  std::set<BasicBlock*> &Blocks) {
  std::vector<BasicBlock *> WorkList;
  WorkList.push_back(InputBB);
  do {
    BasicBlock *BB = WorkList.back(); WorkList.pop_back();
    if (Blocks.insert(BB).second && BB != StopBlock)


      for (pred_iterator I = pred_begin(BB), E = pred_end(BB); I != E; ++I) {
        BasicBlock *WBB = *I;
        WorkList.push_back(WBB);
      }
  } while(!WorkList.empty());
}
