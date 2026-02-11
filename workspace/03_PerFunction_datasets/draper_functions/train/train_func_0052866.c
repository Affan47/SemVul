ProcessIntersections(const long64 botY, const long64 topY)
{
  if( !m_ActiveEdges ) return true;
  try {
    BuildIntersectList(botY, topY);
    if ( !m_IntersectNodes) return true;
    if ( FixupIntersections() ) ProcessIntersectList();
    else return false;
  }
  catch(...) {
    m_SortedEdges = 0;
    DisposeIntersectNodes();
    throw clipperException("ProcessIntersections error");
  }
  return true;
}
