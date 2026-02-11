GetBestDestForJumpOnUndef(BasicBlock *BB) {
  TerminatorInst *BBTerm = BB->getTerminator();
  unsigned MinSucc = 0;
  BasicBlock *TestBB = BBTerm->getSuccessor(MinSucc);

  unsigned MinNumPreds = std::distance(pred_begin(TestBB), pred_end(TestBB));
  for (unsigned i = 1, e = BBTerm->getNumSuccessors(); i != e; ++i) {
    TestBB = BBTerm->getSuccessor(i);
    unsigned NumPreds = std::distance(pred_begin(TestBB), pred_end(TestBB));
    if (NumPreds < MinNumPreds) {
      MinSucc = i;
      MinNumPreds = NumPreds;
    }
  }

  return MinSucc;
}
