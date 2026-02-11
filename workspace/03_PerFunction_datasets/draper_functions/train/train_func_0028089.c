ParseTowerRecord()
{
    RET_IF_FAIL(assertMinCol(6));

    RET_IF_FAIL(readLatLon(&dfLatTower, &dfLonTower, 1));


    RET_IF_FAIL(readDoubleWithBoundsAndConversion(&dfHeightTower, 3, "tower height", FEET_TO_METER, 0., 300.));


    osTowerName = readStringUntilEnd(5);

    bTowerFound = TRUE;
}
