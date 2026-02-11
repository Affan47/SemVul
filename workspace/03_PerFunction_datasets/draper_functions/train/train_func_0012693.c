OGRGeometryShadow_GetPoints(OGRGeometryShadow *self,int *pnCount,double **ppadfXY,double **ppadfZ,int nCoordDimension=0){
    int nPoints = OGR_G_GetPointCount(self);
    *pnCount = nPoints;
    if (nPoints == 0)
    {
        *ppadfXY = NULL;
        *ppadfZ = NULL;
    }
    *ppadfXY = (double*)VSIMalloc(2 * sizeof(double) * nPoints);
    if (*ppadfXY == NULL)
    {
        CPLError(CE_Failure, CPLE_OutOfMemory, "Cannot allocate resulting array");
        *pnCount = 0;
        return;
    }
    if (nCoordDimension <= 0)
        nCoordDimension = OGR_G_GetCoordinateDimension(self);
    *ppadfZ = (nCoordDimension == 3) ? (double*)VSIMalloc(sizeof(double) * nPoints) : NULL;
    OGR_G_GetPoints(self,
                    *ppadfXY, 2 * sizeof(double),
                    (*ppadfXY) + 1, 2 * sizeof(double),
                    *ppadfZ, sizeof(double));
  }
