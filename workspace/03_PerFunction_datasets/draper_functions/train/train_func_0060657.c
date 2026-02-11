amdlibMergeVis2(amdlibVIS2      *vis1,
                                 amdlibVIS2      *vis2,
                                 amdlibBOOLEAN   isInverted,
                                 amdlibERROR_MSG errMsg)
{
    amdlibVIS2 mergedVis2 = {NULL};
    amdlibVIS2 *v1, *v2;

    amdlibLogTrace("amdlibMergeVis2()");


    if (vis1->nbBases != vis2->nbBases)
    {
        amdlibSetErrMsg("Different number of baselines (%d and %d)",
                        vis1->nbBases, vis2->nbBases);
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


    mergedVis2.thisPtr = NULL;
    if (amdlibAllocateVis2(&mergedVis2, vis1->nbFrames, vis1->nbBases,
                           vis1->nbWlen + vis2->nbWlen) != amdlibSUCCESS)
    {
        amdlibSetErrMsg("Could not allocate memory for merged OI-VIS2 structure");
        return amdlibFAILURE;
    }
    if (amdlibCopyVis2From(&mergedVis2, v1, 0, v1->nbWlen,
                           errMsg) != amdlibSUCCESS)
    {
        return amdlibFAILURE;
    }

    if (amdlibCopyVis2From(&mergedVis2, v2, v1->nbWlen, v2->nbWlen,
                           errMsg) != amdlibSUCCESS)
    {
        return amdlibFAILURE;
    }

    free(vis1->table[0].vis2);
    free(vis1->table[0].vis2Error);
    free(vis1->table[0].flag);

    free(vis1->table);
    vis1->nbWlen = mergedVis2.nbWlen;
    vis1->nbFrames = mergedVis2.nbFrames;
    vis1->table = mergedVis2.table;

    return amdlibSUCCESS;
}
