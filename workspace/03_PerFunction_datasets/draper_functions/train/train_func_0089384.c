SetWindingCount(TEdge &edge)
{
  TEdge *e = edge.prevInAEL;

  while ( e  && e->polyType != edge.polyType ) e = e->prevInAEL;
  if ( !e )
  {
    edge.windCnt = edge.windDelta;
    edge.windCnt2 = 0;
    e = m_ActiveEdges;
  } else if ( IsEvenOddFillType(edge) )
  {

    edge.windCnt = 1;
    edge.windCnt2 = e->windCnt2;
    e = e->nextInAEL;
  } else
  {

    if ( e->windCnt * e->windDelta < 0 )
    {
      if (Abs(e->windCnt) > 1)
      {
        if (e->windDelta * edge.windDelta < 0) edge.windCnt = e->windCnt;
        else edge.windCnt = e->windCnt + edge.windDelta;
      } else
        edge.windCnt = e->windCnt + e->windDelta + edge.windDelta;
    } else
    {
      if ( Abs(e->windCnt) > 1 && e->windDelta * edge.windDelta < 0)
        edge.windCnt = e->windCnt;
      else if ( e->windCnt + edge.windDelta == 0 )
        edge.windCnt = e->windCnt;
      else edge.windCnt = e->windCnt + edge.windDelta;
    }
    edge.windCnt2 = e->windCnt2;
    e = e->nextInAEL;
  }


  if ( IsEvenOddAltFillType(edge) )
  {

    while ( e != &edge )
    {
      edge.windCnt2 = (edge.windCnt2 == 0) ? 1 : 0;
      e = e->nextInAEL;
    }
  } else
  {

    while ( e != &edge )
    {
      edge.windCnt2 += e->windDelta;
      e = e->nextInAEL;
    }
  }
}
