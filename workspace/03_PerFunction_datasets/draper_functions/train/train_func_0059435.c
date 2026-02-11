test_resurrect_dataset(hid_t fapl)
{
    hid_t       f = -1, s = -1, d = -1;
    char	filename[1024];

    TESTING("resurrecting dataset after deletion");


    h5_fixname(FILENAME[6], fapl, filename, sizeof filename);


    if((f = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0) FAIL_STACK_ERROR


    if((s = H5Screate(H5S_SCALAR)) < 0) FAIL_STACK_ERROR
    if((d = H5Dcreate2(f, DATASETNAME, H5T_NATIVE_INT, s, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) FAIL_STACK_ERROR
    if(H5Sclose(s) < 0) FAIL_STACK_ERROR


    if(H5Ldelete(f, DATASETNAME, H5P_DEFAULT) < 0) FAIL_STACK_ERROR


    if(H5Iget_name(d, NULL, (size_t)0) != 0) FAIL_STACK_ERROR


    if(H5Lcreate_hard(d, ".", f, DATASET2NAME, H5P_DEFAULT, H5P_DEFAULT) < 0) FAIL_STACK_ERROR


    if(H5Dclose(d) < 0) FAIL_STACK_ERROR
    if(H5Fclose(f) < 0) FAIL_STACK_ERROR


    if((f = H5Fopen(filename, H5F_ACC_RDONLY, fapl)) < 0) FAIL_STACK_ERROR


    if((d = H5Dopen2(f, DATASET2NAME, H5P_DEFAULT)) < 0) FAIL_STACK_ERROR


    if(H5Dclose(d) < 0) FAIL_STACK_ERROR
    if(H5Fclose(f) < 0) FAIL_STACK_ERROR

    PASSED();
    return 0;

error:
    H5E_BEGIN_TRY {
	H5Sclose(s);
	H5Dclose(d);
	H5Fclose(f);
    } H5E_END_TRY;
    return 1;
}
