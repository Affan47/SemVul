amdlibCalibrateRawData(amdlibDARK_DATA *dark,
                                        amdlibRAW_DATA  *rawData,
                                        amdlibERROR_MSG errMsg)
{
    int   iFrame;
    int   iRow, iCol, iRegion;

    amdlibLogTrace("amdlibCalibrateRawData()");


    if (rawData->dataLoaded == amdlibFALSE)
    {
        amdlibSetErrMsg("The raw data structure does not "
                        "contain data. Check call to amdlibLoadRawData()");
        return amdlibFAILURE;
    }


    if (rawData->dataCalibrated == amdlibTRUE)
    {
        amdlibSetErrMsg("The data has been already calibrated");
        return amdlibFAILURE;
    }


    if (amdlibCheckDataCompatibility(dark, rawData,
                                     errMsg) != amdlibSUCCESS)
    {
        return amdlibFAILURE;
    }


    for (iRow = 0; iRow < rawData->nbRows; iRow++)
    {
        for (iCol = 0; iCol < rawData->nbCols; iCol++)
        {
            iRegion = iRow * rawData->nbCols + iCol;

            if (rawData->region[iRegion].corner[0] == 0)
            {
                rawData->region[iRegion].corner[0]  = 1;
            }
            if (rawData->region[iRegion].corner[1] == 0)
            {
                rawData->region[iRegion].corner[1]  = 1;
            }
            if (rawData->variance[iRegion].corner[0] == 0)
            {
                rawData->variance[iRegion].corner[0]  = 1;
            }
            if (rawData->variance[iRegion].corner[1] == 0)
            {
                rawData->variance[iRegion].corner[1]  = 1;
            }
        }
    }


    if (amdlibDiscardNullFrames(rawData, errMsg) != amdlibSUCCESS)
    {
        return amdlibFAILURE;
    }


    if (!(amdlibGetUserPref(amdlibNO_BIAS).set==amdlibTRUE))
    {
        if (amdlibRemoveGlobalBias(rawData, errMsg) != amdlibSUCCESS)
        {
            return amdlibFAILURE;
        }
    }


    if (dark!=NULL)
      {
          if (amdlibSubstractDark(dark, rawData, errMsg) != amdlibSUCCESS)
          {
              return amdlibFAILURE;
          }
      }


    for (iFrame = 0; iFrame < rawData->region[0].dimAxis[2]; iFrame++)
      {

        if (amdlibCalibrateImage(rawData, iFrame, errMsg) != amdlibSUCCESS)
        {
            return amdlibFAILURE;
        }
    }


    if (amdlibREMANENCE != 0)
    {
        if (amdlibSubstractRemanence(rawData, errMsg) != amdlibSUCCESS)
        {
            return amdlibFAILURE;
        }
    }


    rawData->dataCalibrated = amdlibTRUE;

    return amdlibSUCCESS;
}
