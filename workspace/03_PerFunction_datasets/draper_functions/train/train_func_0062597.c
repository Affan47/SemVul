create_file(hid_t *file, H5F_t **f, hid_t fapl)
{
    char	filename[1024];


    h5_fixname(FILENAME[0], fapl, filename, sizeof(filename));


    if((*file = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0)
        TEST_ERROR


    if(NULL == (*f = (H5F_t *)H5I_object(*file)))
        STACK_ERROR


    return(0);

error:
    return(-1);
}
