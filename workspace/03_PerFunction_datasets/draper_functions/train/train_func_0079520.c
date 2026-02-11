populateWithSourcesOfDivergence() {
  Worklist.clear();
  DV.clear();
  for (auto &I : instructions(F)) {
    if (TTI.isSourceOfDivergence(&I)) {
      Worklist.push_back(&I);
      DV.insert(&I);
    }
  }
  for (auto &Arg : F.args()) {
    if (TTI.isSourceOfDivergence(&Arg)) {
      Worklist.push_back(&Arg);
      DV.insert(&Arg);
    }
  }
}
