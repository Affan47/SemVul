make_shuffle(hid_t loc_id)
{
    hid_t    dcpl;
    hid_t    sid;
    hsize_t  dims[RANK]={DIM1,DIM2};
    hsize_t  chunk_dims[RANK]={CDIM1,CDIM2};
    int      buf[DIM1][DIM2];
    int      i, j, n;

    for (i=n=0; i<DIM1; i++)
    {
        for (j=0; j<DIM2; j++)
        {
            buf[i][j]=n++;
        }
    }

    if((sid = H5Screate_simple(RANK, dims, NULL)) < 0)
        return -1;

    if ((dcpl = H5Pcreate(H5P_DATASET_CREATE)) < 0)
        goto out;

    if(H5Pset_chunk(dcpl, RANK, chunk_dims) < 0)
        goto out;


#if defined (H5_HAVE_FILTER_SHUFFLE)

    if (H5Pset_shuffle(dcpl) < 0)
        goto out;
    if (make_dset(loc_id,"dset_shuffle",sid,dcpl,buf) < 0)
        goto out;
#endif


    if(H5Sclose(sid) < 0)
        goto out;
    if(H5Pclose(dcpl) < 0)
        goto out;

    return 0;

out:
    H5E_BEGIN_TRY {
        H5Pclose(dcpl);
        H5Sclose(sid);
    } H5E_END_TRY;
    return -1;
}
