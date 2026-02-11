UpdateMBR(TABMAPFile * poMapFile )
{
    OGRGeometry *poGeom;
    OGREnvelope sEnvelope;


    poGeom = GetGeometryRef();
    if ( (poGeom && wkbFlatten(poGeom->getGeometryType()) == wkbPolygon ) ||
         (poGeom && wkbFlatten(poGeom->getGeometryType()) == wkbPoint )  )
        poGeom->getEnvelope(&sEnvelope);
    else
    {
        CPLError(CE_Failure, CPLE_AssertionFailed,
                 "TABEllipse: Missing or Invalid Geometry!");
        return -1;
    }


    double      dXCenter, dYCenter;
    dXCenter = (sEnvelope.MaxX + sEnvelope.MinX)/2.0;
    dYCenter = (sEnvelope.MaxY + sEnvelope.MinY)/2.0;
    if (m_dXRadius == 0.0 && m_dYRadius == 0.0)
    {
        m_dXRadius = ABS(sEnvelope.MaxX - sEnvelope.MinX) / 2.0;
        m_dYRadius = ABS(sEnvelope.MaxY - sEnvelope.MinY) / 2.0;
    }

    m_dXMin = dXCenter - m_dXRadius;
    m_dYMin = dYCenter - m_dYRadius;
    m_dXMax = dXCenter + m_dXRadius;
    m_dYMax = dYCenter + m_dYRadius;

    if (poMapFile)
    {
        poMapFile->Coordsys2Int(m_dXMin, m_dYMin, m_nXMin, m_nYMin);
        poMapFile->Coordsys2Int(m_dXMax, m_dYMax, m_nXMax, m_nYMax);
    }

    return 0;
}
