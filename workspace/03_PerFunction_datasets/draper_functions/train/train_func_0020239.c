FixupIntersections()
{
  if ( !m_IntersectNodes->next ) return true;

  CopyAELToSEL();
  IntersectNode *int1 = m_IntersectNodes;
  IntersectNode *int2 = m_IntersectNodes->next;
  while (int2)
  {
    TEdge *e1 = int1->edge1;
    TEdge *e2;
    if (e1->prevInSEL == int1->edge2) e2 = e1->prevInSEL;
    else if (e1->nextInSEL == int1->edge2) e2 = e1->nextInSEL;
    else
    {


      while (int2)
      {
        if (int2->edge1->nextInSEL == int2->edge2 ||
          int2->edge1->prevInSEL == int2->edge2) break;
        else int2 = int2->next;
      }
      if ( !int2 ) return false;


      SwapIntersectNodes(*int1, *int2);
      e1 = int1->edge1;
      e2 = int1->edge2;
    }
    SwapPositionsInSEL(e1, e2);
    int1 = int1->next;
    int2 = int1->next;
  }

  m_SortedEdges = 0;


  return (int1->edge1->prevInSEL == int1->edge2 ||
    int1->edge1->nextInSEL == int1->edge2);
}
