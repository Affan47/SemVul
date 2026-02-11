clearColors(BallLarusNode::NodeColor color) {
  for (BLNodeIterator nodeIt = _nodes.begin(); nodeIt != _nodes.end(); nodeIt++)
    (*nodeIt)->setColor(color);
}
