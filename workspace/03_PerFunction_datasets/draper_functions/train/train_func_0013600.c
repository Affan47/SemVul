getPathBlocks() const {
  BallLarusNode* currentNode = _ppi->_currentDag->getRoot ();
  unsigned int increment = _number;
  ProfilePathBlockVector* pbv = new ProfilePathBlockVector;

  while (currentNode != _ppi->_currentDag->getExit()) {
    BallLarusEdge* next = getNextEdge(currentNode, increment);
    increment -= next->getWeight();


    if( next->getType() == BallLarusEdge::NORMAL)
      pbv->push_back (currentNode->getBlock());

    else if( next->getTarget() == _ppi->_currentDag->getExit() ) {
      pbv->push_back (currentNode->getBlock());
      pbv->push_back (next->getRealEdge()->getTarget()->getBlock());
    }


    currentNode = next->getTarget();
  }

  return pbv;
}
