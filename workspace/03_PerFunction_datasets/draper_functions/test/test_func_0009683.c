nextNodeOfGivenNodeOnCurrentBranch(Node *current, unsigned int entryIndex)
{
  Node* temp = entries[entryIndex];
  while(temp->getNodeType()!=FIX_NODE)
    {
      if(temp==current)
        {
          return temp->getOutNode(temp->getTreeOutEdgeIndex());
        }
      temp = temp->getOutNode(temp->getTreeOutEdgeIndex());
    }
  return NULL;
}
