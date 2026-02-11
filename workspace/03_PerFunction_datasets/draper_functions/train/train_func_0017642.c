amdlibReallocateVis2(amdlibVIS2 *vis2,
                                      const int  nbFrames,
                                      const int  nbBases,
                                      const int  nbWlen)
{
    int arraySize = nbWlen * sizeof(double);
    int nbSamples = nbFrames * nbBases;
    int i;
    void *pointer;

    vis2->table = realloc(vis2->table,
                          nbSamples * sizeof(amdlibVIS2_TABLE_ENTRY));
    if (vis2->table == NULL)
    {
        return amdlibFAILURE;
    }

    vis2->table[0].vis2 = realloc(vis2->table[0].vis2, nbSamples * arraySize);
    if (vis2->table[0].vis2 == NULL)
    {
        return amdlibFAILURE;
    }

    for (i = 0, pointer = vis2->table[0].vis2;
         i < nbSamples;
         i++, pointer += arraySize)
    {
        vis2->table[i].vis2 = pointer;
    }

    vis2->table[0].vis2Error = realloc(vis2->table[0].vis2Error,
                                       nbSamples * arraySize);
    if (vis2->table[0].vis2Error == NULL)
    {
        amdlibFreeVis2(vis2);
        return amdlibFAILURE;
    }

    for (i = 0, pointer = vis2->table[0].vis2Error;
         i < nbSamples;
         i++, pointer += arraySize)
    {
        vis2->table[i].vis2Error = pointer;
    }

    arraySize = nbWlen * sizeof(amdlibBOOLEAN);
    vis2->table[0].flag = realloc(vis2->table[0].flag, nbSamples * arraySize);
    if (vis2->table[0].flag == NULL)
    {
        return amdlibFAILURE;
    }

    for (i = 0, pointer = vis2->table[0].flag;
         i < nbSamples;
         i++, pointer += arraySize)
    {
        vis2->table[i].flag = pointer;
    }

    vis2->nbFrames = nbFrames;
    return amdlibSUCCESS;
}
