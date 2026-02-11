getNodePointer(int n) const
{
  int entrySize = entries.size();
  int nodesSize = nodes.size();
  int fixSize = fixes.size();
  if(n>=0 && n<entrySize)
    {
      return entries[n];
    }
  if(n>=entrySize && n<nodesSize+entrySize)
    {
      return nodes[n-entrySize];
    }
  if(n>=nodesSize+entrySize && n<nodesSize+entrySize+fixSize)
    {
      return fixes[n-entrySize-nodesSize];
    }
  return NULL;
}
