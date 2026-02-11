clearEdges(PathList& edges)
{
  for (PathList::const_iterator
        i=edges.begin(), e=edges.end();
        i!=e; ++i)
  {
    delete *i;
  }
  edges.clear();
}
