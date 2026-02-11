amdlibCopyOiArray(amdlibOI_ARRAY  *srcOiArray,
                                   amdlibOI_ARRAY  *dstOiArray,
                                   amdlibERROR_MSG errMsg)
{
    int s, i;


    if (dstOiArray->thisPtr != dstOiArray)
    {
        dstOiArray->thisPtr = dstOiArray;
    }


    dstOiArray->nbStations = srcOiArray->nbStations;
    strcpy(dstOiArray->arrayName, srcOiArray->arrayName);
    strcpy(dstOiArray->coordinateFrame, srcOiArray->coordinateFrame);
    for (i=0; i < 3; i++)
    {
        dstOiArray->arrayCenterCoordinates[i] =
            srcOiArray->arrayCenterCoordinates[i];
    }


    for (s=0; s < dstOiArray->nbStations; s++)
    {
        strcpy(dstOiArray->element[s].telescopeName,
               srcOiArray->element[s].telescopeName);
        strcpy(dstOiArray->element[s].stationName,
               srcOiArray->element[s].stationName);
        dstOiArray->element[s].stationIndex =
            srcOiArray->element[s].stationIndex;
        dstOiArray->element[s].elementDiameter =
            srcOiArray->element[s].elementDiameter;
        for (i=0; i < 3; i++)
        {
            dstOiArray->element[s].stationCoordinates[i] =
                srcOiArray->element[s].stationCoordinates[i];
        }
    }

    return amdlibSUCCESS;
}
