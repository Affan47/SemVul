cmsStageAllocCLutFloat(cmsContext ContextID,
                                       cmsUInt32Number nGridPoints,
                                       cmsUInt32Number inputChan,
                                       cmsUInt32Number outputChan,
                                       const cmsFloat32Number* Table)
{
   cmsUInt32Number Dimensions[MAX_INPUT_DIMENSIONS];
   int i;


    for (i=0; i < MAX_INPUT_DIMENSIONS; i++)
        Dimensions[i] = nGridPoints;

    return cmsStageAllocCLutFloatGranular(ContextID, Dimensions, inputChan, outputChan, Table);
}
