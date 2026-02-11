Winding (int nPt) const
{
  int askTo = pData[nPt].askForWindingB;
  if (askTo < 0 || askTo >= numberOfEdges())
    return 0;
  if (getEdge(askTo).st < getEdge(askTo).en)
    {
      return swdData[askTo].leW;
    }
  else
    {
      return swdData[askTo].riW;
    }
  return 0;
}
