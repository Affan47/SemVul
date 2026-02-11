ParseRecord()
{
    double dfLat, dfLon;
    CPLString osName;

    RET_IF_FAIL(readLatLon(&dfLat, &dfLon, 0));
    osName = readStringUntilEnd(2);

    if (poFIXLayer)
        poFIXLayer->AddFeature(osName, dfLat, dfLon);
}
