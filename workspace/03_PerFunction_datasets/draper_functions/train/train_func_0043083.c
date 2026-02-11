populateWorklist(Loop &L, SmallVector<LoopVector, 8> &V) {

  DEBUG(dbgs() << "Calling populateWorklist called\n");
  LoopVector LoopList;
  Loop *CurrentLoop = &L;
  const std::vector<Loop *> *Vec = &CurrentLoop->getSubLoops();
  while (!Vec->empty()) {


    if (Vec->size() != 1) {
      LoopList.clear();
      return;
    }
    LoopList.push_back(CurrentLoop);
    CurrentLoop = Vec->front();
    Vec = &CurrentLoop->getSubLoops();
  }
  LoopList.push_back(CurrentLoop);
  V.push_back(std::move(LoopList));
}
