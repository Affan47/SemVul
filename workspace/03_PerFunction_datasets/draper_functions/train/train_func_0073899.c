ensMapperCalculateMemsize(const EnsPMapper mapper)
{
    void **keyarray1 = NULL;
    void **valarray1 = NULL;

    void **valarray2 = NULL;

    register ajuint i = 0U;
    register ajuint j = 0U;

    size_t size = 0;

    AjIList iter = NULL;

    EnsPMapperpair mp = NULL;

    if (!mapper)
        return 0;

    size += sizeof (EnsOMapper);

    if (mapper->TypeSource)
    {
        size += sizeof (AjOStr);

        size += ajStrGetRes(mapper->TypeSource);
    }

    if (mapper->TypeTarget)
    {
        size += sizeof (AjOStr);

        size += ajStrGetRes(mapper->TypeTarget);
    }

    size += ensCoordsystemCalculateMemsize(mapper->CoordsystemSource);
    size += ensCoordsystemCalculateMemsize(mapper->CoordsystemTarget);


    size += sizeof (AjOTable);

    ajTableToarrayKeysValues(mapper->Mapperpairs, &keyarray1, &valarray1);

    for (i = 0U; valarray1[i]; i++)
    {


        size += sizeof (AjOStr);

        size += ajStrGetRes((AjPStr) keyarray1[i]);


        size += sizeof (AjOTable);

        ajTableToarrayValues(valarray1[i], &valarray2);

        for (j = 0U; valarray2[j]; j++)
        {


            size += sizeof (ajuint);


            size += sizeof (AjOList);

            iter = ajListIterNew((AjPList) valarray2[j]);

            while (!ajListIterDone(iter))
            {


                mp = (EnsPMapperpair) ajListIterGet(iter);

                size += ensMapperpairCalculateMemsize(mp);
            }

            ajListIterDel(&iter);
        }

        AJFREE(valarray2);
    }

    AJFREE(keyarray1);
    AJFREE(valarray1);

    return size;
}
