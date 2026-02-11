setTreeBranchUp(Node* current, Node* start, double rnp)
{
  while(current!=start)
    {
      current->addInDegree();
      current->setTreeNode();
      if(rnp>current->getDrawingRNP())
        {
          current->setDrawingRNP(rnp);
        }
      current->getPrevTreeEdge()->setTreeEdge();
      if(rnp>current->getPrevTreeEdge()->getDrawingRNP())
        {
          current->getPrevTreeEdge()->setDrawingRNP(rnp);
        }
      layerUsedIndex[current->getLayer()] = current->getLayerIndex();
      current = current->getPrevTreeNode();
    }
}
