IsRingClosed(const OGRLinearRing *poRing)
{
    int nPoints;

    nPoints = poRing->getNumPoints();
    if (nPoints < 3)
	return FALSE;

    if (poRing->getX(0) == poRing->getX(nPoints-1) &&
	poRing->getY(0) == poRing->getY(nPoints-1))
	return TRUE;

    return FALSE;
}
