amdlibMergeVis3(amdlibVIS3      *vis1,
                                 amdlibVIS3      *vis2,
                                 amdlibBOOLEAN   isInverted,
                                 amdlibERROR_MSG errMsg)
{
    amdlibVIS3 mergedVis3 = {NULL};
    amdlibVIS3 *v1, *v2;

    amdlibLogTrace("amdlibMergeVis3()");


    if (vis1->nbClosures != vis2->nbClosures)
    {
        amdlibSetErrMsg("Different number of closures (%d and %d)",
                        vis1->nbClosures, vis2->nbClosures);
        return amdlibFAILURE;
    }


    mergedVis3.thisPtr = NULL;
    if (amdlibAllocateVis3(&mergedVis3, vis1->nbFrames, vis1->nbClosures,
                           vis1->nbWlen + vis2->nbWlen) != amdlibSUCCESS)
    {
        amdlibSetErrMsg("Could not allocate memory for merged OI-VIS3 structure");
        return amdlibFAILURE;
    }

    if (isInverted == amdlibTRUE)
    {
        v1 = vis2;
        v2 = vis1;
    }
    else
    {
        v1 = vis1;
        v2 = vis2;
    }

    if (amdlibCopyVis3From(&mergedVis3, v1, 0, v1->nbWlen,
                           errMsg) != amdlibSUCCESS)
    {
        return amdlibFAILURE;
    }

    if (amdlibCopyVis3From(&mergedVis3, v2, v1->nbWlen, v2->nbWlen,
                           errMsg) != amdlibSUCCESS)
    {
        return amdlibFAILURE;
    }


    free(vis1->table[0].vis3Amplitude);
    free(vis1->table[0].vis3AmplitudeError);
    free(vis1->table[0].vis3Phi);
    free(vis1->table[0].vis3PhiError);
    free(vis1->table[0].flag);

    free(vis1->table);
    vis1->nbWlen = mergedVis3.nbWlen;
    vis1->nbFrames = mergedVis3.nbFrames;
    vis1->table = mergedVis3.table;

    return amdlibSUCCESS;
}
