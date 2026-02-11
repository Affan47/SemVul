GetVertex(uint32 ix, trpg3dPoint &pt) const
{
    if (ix < lightPoints.size() ) {
        pt = lightPoints[ix];
        return true;
    }
    else
        return false;
}
