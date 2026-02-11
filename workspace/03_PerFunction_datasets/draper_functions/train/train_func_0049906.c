gent_array6(void)
{
    hvl_t wdata[SPACE1_DIM1][ARRAY1_DIM1];
    hid_t  fid1;
    hid_t  dataset;
    hid_t  sid1;
    hid_t  tid1;
    hid_t  tid2;
    hsize_t  sdims1[] = {SPACE1_DIM1};
    hsize_t  tdims1[] = {ARRAY1_DIM1};
    int        i,j,k;
    herr_t  ret;


    for(i=0; i<SPACE1_DIM1; i++)
        for(j=0; j<ARRAY1_DIM1; j++) {
            wdata[i][j].p=HDmalloc((i+j+1)*sizeof(unsigned int));
            wdata[i][j].len=i+j+1;
            for(k=0; k<(i+j+1); k++)
                ((unsigned int *)wdata[i][j].p)[k]=i*100+j*10+k;
        }


    fid1 = H5Fcreate(FILE30, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);


    sid1 = H5Screate_simple(SPACE1_RANK, sdims1, NULL);


    tid2 = H5Tvlen_create(H5T_NATIVE_UINT);


    tid1 = H5Tarray_create2(tid2, ARRAY1_RANK, tdims1);


    ret = H5Tclose(tid2);
    HDassert(ret >= 0);


    dataset = H5Dcreate2(fid1, "Dataset1", tid1, sid1, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);


    ret = H5Dwrite(dataset, tid1, H5S_ALL, H5S_ALL, H5P_DEFAULT, wdata);
    HDassert(ret >= 0);


    ret = H5Dvlen_reclaim(tid1, sid1, H5P_DEFAULT, wdata);
    HDassert(ret >= 0);


    ret = H5Dclose(dataset);
    HDassert(ret >= 0);
    ret = H5Tclose(tid1);
    HDassert(ret >= 0);
    ret = H5Sclose(sid1);
    HDassert(ret >= 0);
    ret = H5Fclose(fid1);
    HDassert(ret >= 0);
}
