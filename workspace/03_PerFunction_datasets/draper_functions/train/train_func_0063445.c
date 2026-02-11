getFirstBlockInPath() const {
  BallLarusNode* root = _ppi->_currentDag->getRoot();
  BallLarusEdge* edge = getNextEdge(root, _number);

  if( edge && (edge->getType() == BallLarusEdge::BACKEDGE_PHONY ||
               edge->getType() == BallLarusEdge::SPLITEDGE_PHONY) )
    return edge->getTarget()->getBlock();

  return root->getBlock();
}
