DisconnectStart (int b)
{
  if (getEdge(b).st < 0)
    return;
  _pts[getEdge(b).st].dO--;
  if (getEdge(b).prevS >= 0)
    {
      if (getEdge(getEdge(b).prevS).st == getEdge(b).st)
        {
          _aretes[getEdge(b).prevS].nextS = getEdge(b).nextS;
        }
      else if (getEdge(getEdge(b).prevS).en == getEdge(b).st)
        {
          _aretes[getEdge(b).prevS].nextE = getEdge(b).nextS;
        }
    }
  if (getEdge(b).nextS >= 0)
    {
      if (getEdge(getEdge(b).nextS).st == getEdge(b).st)
        {
          _aretes[getEdge(b).nextS].prevS = getEdge(b).prevS;
        }
      else if (getEdge(getEdge(b).nextS).en == getEdge(b).st)
        {
          _aretes[getEdge(b).nextS].prevE = getEdge(b).prevS;
        }
    }
  if (getPoint(getEdge(b).st).incidentEdge[FIRST] == b)
    _pts[getEdge(b).st].incidentEdge[FIRST] = getEdge(b).nextS;
  if (getPoint(getEdge(b).st).incidentEdge[LAST] == b)
    _pts[getEdge(b).st].incidentEdge[LAST] = getEdge(b).prevS;
  _aretes[b].st = -1;
}
