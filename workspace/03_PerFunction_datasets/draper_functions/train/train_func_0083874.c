calculateSpanningTree() {
  std::stack<BallLarusNode*> dfsStack;

  for(BLNodeIterator nodeIt = _nodes.begin(), end = _nodes.end();
      nodeIt != end; nodeIt++) {
    (*nodeIt)->setColor(BallLarusNode::WHITE);
  }

  dfsStack.push(getRoot());
  while(dfsStack.size() > 0) {
    BallLarusNode* node = dfsStack.top();
    dfsStack.pop();

    if(node->getColor() == BallLarusNode::WHITE)
      continue;

    BallLarusNode* nextNode;
    bool forward = true;
    BLEdgeIterator succEnd = node->succEnd();

    node->setColor(BallLarusNode::WHITE);

    for(BLEdgeIterator edge = node->succBegin(), predEnd = node->predEnd();
        edge != predEnd; edge++) {
      if(edge == succEnd) {
        edge = node->predBegin();
        forward = false;
      }


      if ((*edge)->getType() == BallLarusEdge::SPLITEDGE)
        continue;

      nextNode = forward? (*edge)->getTarget(): (*edge)->getSource();
      if(nextNode->getColor() != BallLarusNode::WHITE) {
        nextNode->setColor(BallLarusNode::WHITE);
        makeEdgeSpanning((BLInstrumentationEdge*)(*edge));
      }
    }
  }

  for(BLEdgeIterator edge = _edges.begin(), end = _edges.end();
      edge != end; edge++) {
    BLInstrumentationEdge* instEdge = (BLInstrumentationEdge*) (*edge);

    if(!instEdge->isInSpanningTree() && (*edge)->getType()
        != BallLarusEdge::SPLITEDGE)
      _chordEdges.push_back(instEdge);
  }
}
