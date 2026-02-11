gent_array4(void)
{
    typedef struct {
            int i;
            float f;
    } s2_t;
    s2_t wdata[SPACE1_DIM1][ARRAY1_DIM1];
    hid_t  fid1;
    hid_t  dataset;
    hid_t  sid1;
    hid_t  tid1;
    hid_t  tid2;
    hsize_t  sdims1[] = {SPACE1_DIM1};
    hsize_t  tdims1[] = {ARRAY1_DIM1};
    int        i,j;
    herr_t  ret;


    for(i=0; i<SPACE1_DIM1; i++)
        for(j=0; j<ARRAY1_DIM1; j++) {
            wdata[i][j].i=i*10+j;
            wdata[i][j].f=(float)(i*2.5+j);
        }


    fid1 = H5Fcreate(FILE28, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);


    sid1 = H5Screate_simple(SPACE1_RANK, sdims1, NULL);


    tid2 = H5Tcreate(H5T_COMPOUND, sizeof(s2_t));


    ret = H5Tinsert(tid2, "i", HOFFSET(s2_t, i), H5T_NATIVE_INT);
    HDassert(ret >= 0);


    ret = H5Tinsert(tid2, "f", HOFFSET(s2_t, f), H5T_NATIVE_FLOAT);
    HDassert(ret >= 0);


    tid1 = H5Tarray_create2(tid2, ARRAY1_RANK, tdims1);


    ret = H5Tclose(tid2);
    HDassert(ret >= 0);


    dataset = H5Dcreate2(fid1, "Dataset1", tid1, sid1, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);


    ret = H5Dwrite(dataset, tid1, H5S_ALL, H5S_ALL, H5P_DEFAULT, wdata);
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
