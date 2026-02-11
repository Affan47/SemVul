FindXDiscontinuity(OGRCoordinateTransformation* poCT,
                               double dfX1, double dfX2, double dfY,
                               double& dfMinX, double& dfMinY, double& dfMaxX, double& dfMaxY,
                               int nRecLevel = 0)
{
    double dfXMid = (dfX1 + dfX2) / 2;

    double dfWrkX1 = TransformAndUpdateBBAndReturnX(poCT, dfX1, dfY, dfMinX, dfMinY, dfMaxX, dfMaxY);
    double dfWrkXMid = TransformAndUpdateBBAndReturnX(poCT, dfXMid, dfY, dfMinX, dfMinY, dfMaxX, dfMaxY);
    double dfWrkX2 = TransformAndUpdateBBAndReturnX(poCT, dfX2, dfY, dfMinX, dfMinY, dfMaxX, dfMaxY);

    double dfDX1 = dfWrkXMid - dfWrkX1;
    double dfDX2 = dfWrkX2 - dfWrkXMid;

    if( dfDX1 * dfDX2 < 0 && nRecLevel < 30)
    {
        FindXDiscontinuity(poCT, dfX1, dfXMid, dfY, dfMinX, dfMinY, dfMaxX, dfMaxY, nRecLevel + 1);
        FindXDiscontinuity(poCT, dfXMid, dfX2, dfY, dfMinX, dfMinY, dfMaxX, dfMaxY, nRecLevel + 1);
    }
}
