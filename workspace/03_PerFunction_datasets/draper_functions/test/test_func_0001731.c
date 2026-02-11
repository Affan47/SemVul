ReadPolygon(int iShape)
{
    int iFigure, iPoint, iNextPoint, i;
    int iNextFigure = NextFigureOffset(iShape);

    OGRPolygon* poPoly = new OGRPolygon();
    for (iFigure = FigureOffset(iShape); iFigure < iNextFigure; iFigure++)
    {
        OGRLinearRing* poRing = new OGRLinearRing();
        iPoint = PointOffset(iFigure);
        iNextPoint = NextPointOffset(iFigure);
        poRing->setNumPoints(iNextPoint - iPoint);
        i = 0;
        while (iPoint < iNextPoint)
        {
            if (nColType == MSSQLCOLTYPE_GEOGRAPHY)
            {
                if ( chProps & SP_HASZVALUES )
                    poRing->setPoint(i, ReadY(iPoint), ReadX(iPoint), ReadZ(iPoint) );
                else
                    poRing->setPoint(i, ReadY(iPoint), ReadX(iPoint) );
            }
            else
            {
                if ( chProps & SP_HASZVALUES )
                    poRing->setPoint(i, ReadX(iPoint), ReadY(iPoint), ReadZ(iPoint) );
                else
                    poRing->setPoint(i, ReadX(iPoint), ReadY(iPoint) );
            }

            ++iPoint;
            ++i;
        }
        poPoly->addRingDirectly( poRing );
    }
    return poPoly;
}
