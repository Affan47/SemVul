amdlibAllocatePiston(amdlibPISTON *piston,
                                      const int    nbFrames,
                                      const int    nbBases)
{
    int band;

    amdlibLogTrace("amdlibAllocatePiston()");


    if (piston->thisPtr == piston)
    {
        amdlibFreePiston(piston);
    }


    piston->thisPtr = memset(piston, '\0', sizeof(*piston));

    piston->nbFrames = nbFrames;
    piston->nbBases  = nbBases;
    for (band = amdlibJ_BAND; band <= amdlibK_BAND; band++)
    {
        piston->bandFlag[band] = amdlibFALSE;
        piston->pistonOPDArray[band] = calloc(nbFrames*nbBases, sizeof(amdlibDOUBLE));
        piston->sigmaPistonArray[band] =
            calloc(nbFrames*nbBases, sizeof(amdlibDOUBLE));
        if ((piston->pistonOPDArray[band] == NULL) ||
            (piston->sigmaPistonArray[band] == NULL))
        {
            amdlibFreePiston(piston);
            return amdlibFAILURE;
        }
    }
    piston->pistonOPD = calloc(nbFrames*nbBases, sizeof(amdlibDOUBLE));
    piston->sigmaPiston = calloc(nbFrames*nbBases, sizeof(amdlibDOUBLE));
    if ((piston->pistonOPD == NULL) || (piston->sigmaPiston == NULL))
    {
        amdlibFreePiston(piston);
        return amdlibFAILURE;
    }


    return amdlibSUCCESS;
}
