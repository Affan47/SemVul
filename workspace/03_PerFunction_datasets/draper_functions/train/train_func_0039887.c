reset()
{
  for(unsigned int i=0; i<entries.size(); i++)
    {
      delete entries[i];
    }
  for(unsigned int i=0; i<nodes.size(); i++)
    {
      delete nodes[i];
    }
  for(unsigned int i=0; i<fixes.size(); i++)
    {
      delete fixes[i];
    }
  for(unsigned int i=0; i<edges.size(); i++)
    {
      delete edges[i];
    }
  entries.clear();
  nodes.clear();
  fixes.clear();
  edges.clear();
  layerUsedIndex.clear();
  layerStartingIndex.clear();
  status = TREE_NOT_GENERATED;
  nodesReadIn = NODES_NOT_READ_IN;
  edgesGenerated = EDGES_NOT_GENERATED;
  treeShapeStatus = BOTTOM_TREE;
}
