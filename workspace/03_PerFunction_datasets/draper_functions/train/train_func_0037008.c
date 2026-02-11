visitBasicBlock(BasicBlock &BB) {
  InstsInThisBlock.clear();


  Assert1(BB.getTerminator(), "Basic Block does not have terminator!", &BB);


  if (isa<PHINode>(BB.front())) {
    SmallVector<BasicBlock*, 8> Preds(pred_begin(&BB), pred_end(&BB));
    SmallVector<std::pair<BasicBlock*, Value*>, 8> Values;
    std::sort(Preds.begin(), Preds.end());
    PHINode *PN;
    for (BasicBlock::iterator I = BB.begin(); (PN = dyn_cast<PHINode>(I));++I) {

      Assert1(PN->getNumIncomingValues() != 0,
              "PHI nodes must have at least one entry.  If the block is dead, "
              "the PHI should be removed!", PN);
      Assert1(PN->getNumIncomingValues() == Preds.size(),
              "PHINode should have one entry for each predecessor of its "
              "parent basic block!", PN);


      Values.clear();
      Values.reserve(PN->getNumIncomingValues());
      for (unsigned i = 0, e = PN->getNumIncomingValues(); i != e; ++i)
        Values.push_back(std::make_pair(PN->getIncomingBlock(i),
                                        PN->getIncomingValue(i)));
      std::sort(Values.begin(), Values.end());

      for (unsigned i = 0, e = Values.size(); i != e; ++i) {


        Assert4(i == 0 || Values[i].first  != Values[i-1].first ||
                Values[i].second == Values[i-1].second,
                "PHI node has multiple entries for the same basic block with "
                "different incoming values!", PN, Values[i].first,
                Values[i].second, Values[i-1].second);


        Assert3(Values[i].first == Preds[i],
                "PHI node entries do not match predecessors!", PN,
                Values[i].first, Preds[i]);
      }
    }
  }
}
