getBBox(int *xMinA, int *yMinA, int *xMaxA, int *yMaxA)
{
  int i;
  int cxMin = splashRound(xMin), cyMin = splashRound(yMin);
  int cxMax = splashRound(xMax), cyMax = splashRound(yMax);
  int txMin, tyMin, txMax, tyMax;

  for (i = 0; i < length; ++i) {
    scanners[i]->getBBox(&txMin,&tyMin,&txMax,&tyMax);
    if (txMin > cxMin) cxMin = txMin;
    if (tyMin > cyMin) cyMin = tyMin;
    if (txMax < cxMax) cxMax = txMax;
    if (tyMax < cyMax) cyMax = tyMax;
  }
  *xMinA = cxMin;
  *yMinA = cyMin;
  *xMaxA = cxMax;
  *yMaxA = cyMax;
}
