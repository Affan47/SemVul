test_resurrect_group(hid_t fapl)
{
    hid_t       file = -1, group = -1;
    char        filename[1024];

    TESTING("resurrecting group after deletion");


    h5_fixname(FILENAME[8], fapl, filename, sizeof filename);


    if((file = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0) FAIL_STACK_ERROR


    if((group = H5Gcreate2(file, GROUPNAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) FAIL_STACK_ERROR


    if(H5Ldelete(file, GROUPNAME, H5P_DEFAULT) < 0) FAIL_STACK_ERROR


    if(H5Iget_name(group, NULL, (size_t)0) != 0) FAIL_STACK_ERROR


    if(H5Lcreate_hard(group, ".", file, GROUP2NAME, H5P_DEFAULT, H5P_DEFAULT) < 0) FAIL_STACK_ERROR


    if(H5Gclose(group) < 0) FAIL_STACK_ERROR
    if(H5Fclose(file) < 0) FAIL_STACK_ERROR


    if((file = H5Fopen(filename, H5F_ACC_RDONLY, fapl)) < 0) FAIL_STACK_ERROR


    if((group = H5Gopen2(file, GROUP2NAME, H5P_DEFAULT)) < 0) FAIL_STACK_ERROR


    if(H5Gclose(group) < 0) FAIL_STACK_ERROR
    if(H5Fclose(file) < 0) FAIL_STACK_ERROR

    PASSED();
    return 0;

error:
    H5E_BEGIN_TRY {
	H5Gclose(group);
	H5Fclose(file);
    } H5E_END_TRY;
    return 1;
}
