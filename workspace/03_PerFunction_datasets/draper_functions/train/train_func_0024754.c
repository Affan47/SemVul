Clear()

{
    if( poRoot )
        delete poRoot;

    poRoot = NULL;

    bNormInfoSet = FALSE;
    dfFromGreenwich = 1.0;
    dfToMeter = 1.0;
    dfToDegrees = 1.0;
}
