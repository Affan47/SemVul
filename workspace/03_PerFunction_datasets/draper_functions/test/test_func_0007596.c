trackRSI(const RegSeqInfo &RSI) {
  for (DenseMap<unsigned, unsigned>::const_iterator
  It = RSI.RegToChan.begin(), E = RSI.RegToChan.end(); It != E; ++It) {
    PreviousRegSeqByReg[(*It).first].push_back(RSI.Instr);
  }
  PreviousRegSeqByUndefCount[RSI.UndefReg.size()].push_back(RSI.Instr);
  PreviousRegSeq[RSI.Instr] = RSI;
}
