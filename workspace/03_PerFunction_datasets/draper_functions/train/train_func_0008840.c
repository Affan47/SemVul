NITFDoLinesIntersect( double dfL1X1, double dfL1Y1,
                                 double dfL1X2, double dfL1Y2,
                                 double dfL2X1, double dfL2Y1,
                                 double dfL2X2, double dfL2Y2 )

{
    double dfL1M, dfL1B, dfL2M, dfL2B;

    if( dfL1X1 == dfL1X2 )
    {
        dfL1M = 1e10;
        dfL1B = 0.0;
    }
    else
    {
        dfL1M = (dfL1Y2 - dfL1Y1 ) / (dfL1X2 - dfL1X1);
        dfL1B = dfL1Y2 - dfL1M * dfL1X2;
    }

    if( dfL2X1 == dfL2X2 )
    {
        dfL2M = 1e10;
        dfL2B = 0.0;
    }
    else
    {
        dfL2M = (dfL2Y2 - dfL2Y1 ) / (dfL2X2 - dfL2X1);
        dfL2B = dfL2Y2 - dfL2M * dfL2X2;
    }

    if( dfL2M == dfL1M )
    {

        return FALSE;
    }
    else
    {
        double dfX, dfY;

        dfX = (dfL2B - dfL1B) / (dfL1M-dfL2M);
        dfY = dfL2M * dfX + dfL2B;


        return ((dfX >= dfL1X1 && dfX <= dfL1X2)
                || (dfX >= dfL1X2 && dfX <= dfL1X1))
                && ((dfX >= dfL2X1 && dfX <= dfL2X2)
                    || (dfX >= dfL2X2 && dfX <= dfL2X1));
    }
}
