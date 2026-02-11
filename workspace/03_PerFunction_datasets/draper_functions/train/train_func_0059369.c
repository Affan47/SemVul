do_file_hyperslab(char* fname)
{

    int32 sd_id;
    int32 sds_id;
    int32 dims[2];
    int32 start[2];
    int32 edges[2];

    int32 sds_idx;
    int32 rank;
	uint8 array_data[DIM0][DIM1];
    uint8 append_data[DIM1];
	intn  i, j, n;


    if ((sd_id = SDstart(fname, DFACC_CREATE))==FAIL)
        goto error;


	rank = 2;
	dims[0] = SD_UNLIMITED;
	dims[1] = DIM1;


	if ((sds_id = SDcreate(sd_id, "data1", DFNT_UINT8, rank, dims))==FAIL)
        goto error;


    for (j = 0; j < DIM0; j++)
    {
        for (i = 0; i < DIM1; i++)
            array_data[j][i] = (i + j) + 1;
    }


    for (i = 0; i < rank; i++)
    {
        start[i] = 0;
    }
	edges[0] = DIM0;
	edges[1] = DIM1;

    if ( SDwritedata(sds_id, start, NULL, edges, (VOIDP)array_data)==FAIL)
        goto error;


    if ( SDendaccess(sds_id)==FAIL)
        goto error;
    if ( SDend(sd_id)==FAIL)
        goto error;


	if (( sd_id = SDstart(fname, DFACC_WRITE))==FAIL)
        goto error;

    if ((sds_idx = SDnametoindex (sd_id, "data1"))==FAIL)
        goto error;
    if ((sds_id = SDselect (sd_id, sds_idx))==FAIL)
        goto error;


    for (i = 0; i < DIM1; i++)
        append_data[i] = i + 1;


    for (n = 0; n < ADD_ROWS; n++)
    {
        start[0] = DIM0 + n;
        start[1] = 0;
        edges[0] = 1;
        edges[1] = DIM1;


        if ( SDwritedata (sds_id, start, NULL, edges, (VOIDP) append_data)==FAIL)
            goto error;

    }


    if ( SDendaccess (sds_id)==FAIL)
        goto error;
    if ( SDend (sd_id)==FAIL)
        goto error;

    return SUCCEED;

error:

    printf("Error...Exiting...\n");

    return FAIL;


}
