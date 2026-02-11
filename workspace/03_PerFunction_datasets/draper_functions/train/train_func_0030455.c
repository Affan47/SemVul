ReadPoint(int iShape)
{
    int iFigure = FigureOffset(iShape);
    if ( iFigure < nNumFigures )
    {
        int iPoint = PointOffset(iFigure);
        if ( iPoint < nNumPoints )
        {
            if (nColType == MSSQLCOLTYPE_GEOGRAPHY)
            {
                if ( chProps & SP_HASZVALUES )
                    return new OGRPoint( ReadY(iPoint), ReadX(iPoint), ReadZ(iPoint) );
                else
                    return new OGRPoint( ReadY(iPoint), ReadX(iPoint) );
            }
            else
            {
                if ( chProps & SP_HASZVALUES )
                    return new OGRPoint( ReadX(iPoint), ReadY(iPoint), ReadZ(iPoint) );
                else
                    return new OGRPoint( ReadX(iPoint), ReadY(iPoint) );
            }
        }
    }
    return NULL;
}
