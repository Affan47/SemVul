RemoveFromWorklist(Instruction *I,
                               std::vector<Instruction*> &Worklist) {
  std::vector<Instruction*>::iterator WI = std::find(Worklist.begin(),
                                                     Worklist.end(), I);
  while (WI != Worklist.end()) {
    unsigned Offset = WI-Worklist.begin();
    Worklist.erase(WI);
    WI = std::find(Worklist.begin()+Offset, Worklist.end(), I);
  }
}
