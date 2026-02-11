test_copy_dataset_simple_samefile(hid_t fcpl, hid_t fapl)
{
    hid_t fid = -1;
    hid_t sid = -1;
    hid_t did = -1, did2 = -1;
    int buf[DIM_SIZE_1][DIM_SIZE_2];
    hsize_t dim2d[2];
    int i, j;
    char filename[NAME_BUF_SIZE];

    TESTING("H5Ocopy(): simple dataset within the same file");


    for (i=0; i<DIM_SIZE_1; i++)
        for (j=0; j<DIM_SIZE_2; j++)
            buf[i][j] = 10000 + 100*i+j;


    h5_fixname(FILENAME[0], fapl, filename, sizeof filename);


    addr_reset();


    if((fid = H5Fcreate(filename, H5F_ACC_TRUNC, fcpl, fapl)) < 0) TEST_ERROR


    dim2d[0] = DIM_SIZE_1;
    dim2d[1] = DIM_SIZE_2;


    if((sid = H5Screate_simple(2, dim2d, NULL)) < 0) TEST_ERROR


    if((did = H5Dcreate2(fid, NAME_DATASET_SIMPLE, H5T_NATIVE_INT, sid, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) TEST_ERROR


    if(H5Dwrite(did, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf) < 0) TEST_ERROR


    if(H5Sclose(sid) < 0) TEST_ERROR


    if(test_copy_attach_attributes(did, H5T_NATIVE_INT) < 0) TEST_ERROR


    if(H5Dclose(did) < 0) TEST_ERROR


    if(H5Fclose(fid) < 0) TEST_ERROR


    if((fid = H5Fopen(filename, H5F_ACC_RDWR, fapl)) < 0) TEST_ERROR


    if(H5Ocopy(fid, NAME_DATASET_SIMPLE, fid, NAME_DATASET_SIMPLE2, H5P_DEFAULT, H5P_DEFAULT) < 0) TEST_ERROR


    if((did = H5Dopen2(fid, NAME_DATASET_SIMPLE, H5P_DEFAULT)) < 0) TEST_ERROR


    if((did2 = H5Dopen2(fid, NAME_DATASET_SIMPLE2, H5P_DEFAULT)) < 0) TEST_ERROR


    if(compare_datasets(did, did2, H5P_DEFAULT, buf) != TRUE) TEST_ERROR


    if(H5Dclose(did2) < 0) TEST_ERROR


    if(H5Dclose(did) < 0) TEST_ERROR


    if(H5Fclose(fid) < 0) TEST_ERROR

    PASSED();
    return 0;

error:
    H5E_BEGIN_TRY {
    	H5Dclose(did2);
    	H5Dclose(did);
    	H5Sclose(sid);
    	H5Fclose(fid);
    } H5E_END_TRY;
    return 1;
}
