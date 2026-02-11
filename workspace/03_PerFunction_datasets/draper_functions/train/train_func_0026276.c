calculatePathNumbers() {
  BallLarusNode* node;
  std::queue<BallLarusNode*> bfsQueue;
  bfsQueue.push(getExit());

  while(bfsQueue.size() > 0) {
    node = bfsQueue.front();

    DEBUG(dbgs() << "calculatePathNumbers on " << node->getName() << "\n");

    bfsQueue.pop();
    unsigned prevPathNumber = node->getNumberPaths();
    calculatePathNumbersFrom(node);


    if( node->getNumberPaths() > 100000000 && node != getRoot() ) {

      BallLarusEdge* exitEdge = addEdge(node, getExit(), 0);
      exitEdge->setType(BallLarusEdge::SPLITEDGE_PHONY);


      BasicBlock* oldTarget = 0;
      unsigned duplicateNumber = 0;


      for( BLEdgeIterator succ = node->succBegin(), end = node->succEnd();
           succ != end; oldTarget = (*succ)->getTarget()->getBlock(), succ++ ) {

        if( (*succ)->getType() == BallLarusEdge::NORMAL ) {

          if( oldTarget != (*succ)->getTarget()->getBlock() )
            duplicateNumber = 0;


          BallLarusEdge* rootEdge =
            addEdge(getRoot(), (*succ)->getTarget(), duplicateNumber++);
          rootEdge->setType(BallLarusEdge::SPLITEDGE_PHONY);
          rootEdge->setRealEdge(*succ);


          (*succ)->setType(BallLarusEdge::SPLITEDGE);
          (*succ)->setPhonyRoot(rootEdge);
          (*succ)->setPhonyExit(exitEdge);
          (*succ)->setWeight(0);
        }
      }

      calculatePathNumbersFrom(node);
    }

    DEBUG(dbgs() << "prev, new number paths " << prevPathNumber << ", "
          << node->getNumberPaths() << ".\n");

    if(prevPathNumber == 0 && node->getNumberPaths() != 0) {
      DEBUG(dbgs() << "node ready : " << node->getName() << "\n");
      for(BLEdgeIterator pred = node->predBegin(), end = node->predEnd();
          pred != end; pred++) {
        if( (*pred)->getType() == BallLarusEdge::BACKEDGE ||
            (*pred)->getType() == BallLarusEdge::SPLITEDGE )
          continue;

        BallLarusNode* nextNode = (*pred)->getSource();

        if(nextNode->getNumberPaths() == 0)
          bfsQueue.push(nextNode);
      }
    }
  }

  DEBUG(dbgs() << "\tNumber of paths: " << getRoot()->getNumberPaths() << "\n");
}
