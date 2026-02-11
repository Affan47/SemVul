BuildHistogram(const Matcher *M, std::vector<unsigned> &OpcodeFreq){
  for (; M != 0; M = M->getNext()) {

    if (unsigned(M->getKind()) >= OpcodeFreq.size())
      OpcodeFreq.resize(M->getKind()+1);
    OpcodeFreq[M->getKind()]++;


    if (const ScopeMatcher *SM = dyn_cast<ScopeMatcher>(M)) {
      for (unsigned i = 0, e = SM->getNumChildren(); i != e; ++i)
        BuildHistogram(SM->getChild(i), OpcodeFreq);
    } else if (const SwitchOpcodeMatcher *SOM =
                 dyn_cast<SwitchOpcodeMatcher>(M)) {
      for (unsigned i = 0, e = SOM->getNumCases(); i != e; ++i)
        BuildHistogram(SOM->getCaseMatcher(i), OpcodeFreq);
    } else if (const SwitchTypeMatcher *STM = dyn_cast<SwitchTypeMatcher>(M)) {
      for (unsigned i = 0, e = STM->getNumCases(); i != e; ++i)
        BuildHistogram(STM->getCaseMatcher(i), OpcodeFreq);
    }
  }
}
