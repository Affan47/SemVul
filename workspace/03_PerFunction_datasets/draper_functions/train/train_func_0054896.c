ComputeSpatiaLiteGeometrySize(const OGRGeometry *poGeometry,
                                                  int bHasM, int bSpatialite2D,
                                                  int bUseComprGeom)
{
    switch (wkbFlatten(poGeometry->getGeometryType()))
    {
        case wkbPoint:
            if ( bSpatialite2D == TRUE )
                return 16;
            else if (poGeometry->getCoordinateDimension() == 3)
            {
                if (bHasM == TRUE)
                    return 32;
                else
                    return 24;
            }
            else
            {
                if (bHasM == TRUE)
                    return 24;
                else
                    return 16;
            }

        case wkbLineString:
        case wkbLinearRing:
        {
            int nPoints = ((OGRLineString*)poGeometry)->getNumPoints();
            int nDimension;
            int nPointsDouble = nPoints;
            int nPointsFloat = 0;
            if ( bSpatialite2D == TRUE )
            {
                nDimension = 2;
                bHasM = FALSE;
            }
            else
            {
                if ( bUseComprGeom && nPoints >= 2 )
                {
                    nPointsDouble = 2;
                    nPointsFloat = nPoints - 2;
                }
                nDimension = poGeometry->getCoordinateDimension();
            }
            return 4 + nDimension * (8 * nPointsDouble + 4 * nPointsFloat) + ((bHasM) ? nPoints * 8 : 0);
        }

        case wkbPolygon:
        {
            int nSize = 4;
            OGRPolygon* poPoly = (OGRPolygon*) poGeometry;
            bUseComprGeom = bUseComprGeom && !bSpatialite2D && CanBeCompressedSpatialiteGeometry(poGeometry);
            if (poPoly->getExteriorRing() != NULL)
            {
                nSize += ComputeSpatiaLiteGeometrySize(poPoly->getExteriorRing(),
                                                       bHasM, bSpatialite2D, bUseComprGeom);

                int nInteriorRingCount = poPoly->getNumInteriorRings();
                for(int i=0;i<nInteriorRingCount;i++)
                    nSize += ComputeSpatiaLiteGeometrySize(poPoly->getInteriorRing(i),
                                                           bHasM, bSpatialite2D, bUseComprGeom );
            }
            return nSize;
        }

        case wkbMultiPoint:
        case wkbMultiLineString:
        case wkbMultiPolygon:
        case wkbGeometryCollection:
        {
            int nSize = 4;
            OGRGeometryCollection* poGeomCollection = (OGRGeometryCollection*) poGeometry;
            int nParts = poGeomCollection->getNumGeometries();
            for(int i=0;i<nParts;i++)
                nSize += 5 + ComputeSpatiaLiteGeometrySize(poGeomCollection->getGeometryRef(i),
                                                           bHasM, bSpatialite2D, bUseComprGeom );
            return nSize;
        }

        default:
            CPLError(CE_Failure, CPLE_AppDefined, "Unexpected geometry type");
            return 0;
    }
}
