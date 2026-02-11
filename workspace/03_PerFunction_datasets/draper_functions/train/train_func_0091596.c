Sub360ToLon( OGRGeometry* poGeom )
{
    switch (wkbFlatten(poGeom->getGeometryType()))
    {
        case wkbPolygon:
        case wkbMultiLineString:
        case wkbMultiPolygon:
        case wkbGeometryCollection:
        {
            int nSubGeomCount = OGR_G_GetGeometryCount((OGRGeometryH)poGeom);
            for( int iGeom = 0; iGeom < nSubGeomCount; iGeom++ )
            {
                Sub360ToLon((OGRGeometry*)OGR_G_GetGeometryRef((OGRGeometryH)poGeom, iGeom));
            }

            break;
        }

        case wkbLineString:
        case wkbLinearRing:
        {
            OGRLineString* poLineString = (OGRLineString* )poGeom;
            int nPointCount = poLineString->getNumPoints();
            int nCoordDim = poLineString->getCoordinateDimension();
            for( int iPoint = 0; iPoint < nPointCount; iPoint++)
            {
                if (nCoordDim == 2)
                    poLineString->setPoint(iPoint,
                                     poLineString->getX(iPoint) - 360,
                                     poLineString->getY(iPoint));
                else
                    poLineString->setPoint(iPoint,
                                     poLineString->getX(iPoint) - 360,
                                     poLineString->getY(iPoint),
                                     poLineString->getZ(iPoint));
            }
            break;
        }

        default:
            break;
    }
}
