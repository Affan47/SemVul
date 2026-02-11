GetCenter(double &dX, double &dY)
{
    if (!m_bCenterIsSet)
    {
        OGRGeometry     *poGeom;
        OGRLineString   *poLine = NULL;

        poGeom = GetGeometryRef();
        if (poGeom && wkbFlatten(poGeom->getGeometryType()) == wkbLineString)
        {
            poLine = (OGRLineString *)poGeom;
        }
        else if (poGeom && wkbFlatten(poGeom->getGeometryType()) == wkbMultiLineString)
        {
            OGRMultiLineString *poMultiLine = (OGRMultiLineString*)poGeom;
            if (poMultiLine->getNumGeometries() > 0)
                poLine = (OGRLineString *)poMultiLine->getGeometryRef(0);
        }

        if (poLine && poLine->getNumPoints() > 0)
        {
            int i = poLine->getNumPoints()/2;
            if (poLine->getNumPoints() % 2 == 0)
            {

                m_dCenterX = (poLine->getX(i-1) + poLine->getX(i))/2.0;
                m_dCenterY = (poLine->getY(i-1) + poLine->getY(i))/2.0;
            }
            else
            {

                m_dCenterX = poLine->getX(i);
                m_dCenterY = poLine->getY(i);
            }
            m_bCenterIsSet = TRUE;
        }
    }

    if (!m_bCenterIsSet)
        return -1;

    dX = m_dCenterX;
    dY = m_dCenterY;
    return 0;
}
