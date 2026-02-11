Int2CoordsysDist(GInt32 nX, GInt32 nY, double &dX, double &dY)
{
    if (m_poHeader == NULL)
        return -1;

    return m_poHeader->Int2CoordsysDist(nX, nY, dX, dY);
}
