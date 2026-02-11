test_fs_create(hid_t fapl)
{
    hid_t		file = -1;
    char		filename[FILENAME_LEN];
    H5F_t		*f = NULL;
    H5FS_t      	*frsp = NULL;
    haddr_t     	fs_addr;
    h5_stat_size_t      file_size, empty_size;
    frspace_state_t 	state;
    H5FS_create_t 	cparam, test_cparam;
    size_t		nclasses;
    unsigned		init_flags=0;

    TESTING("the creation/close/reopen/deletion of the free-space manager");


    h5_fixname(FILENAME[0], fapl, filename, sizeof(filename));


    if((file = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0)
        FAIL_STACK_ERROR


    if(H5Fclose(file) < 0)
        FAIL_STACK_ERROR


    if((empty_size = h5_get_file_size(filename, fapl)) < 0)
        TEST_ERROR


    if((file = H5Fopen(filename, H5F_ACC_RDWR, fapl)) < 0)
        FAIL_STACK_ERROR


    if(NULL == (f = (H5F_t *)H5I_object(file)))
        FAIL_STACK_ERROR


    init_cparam(&cparam);
    nclasses = NELMTS(test_classes);

    if(NULL == (frsp = H5FS_create(f, H5P_DATASET_XFER_DEFAULT, &fs_addr,
	    &cparam, nclasses, test_classes, &init_flags, (hsize_t)FSPACE_THRHD_DEF, (hsize_t)FSPACE_ALIGN_DEF)))
	FAIL_STACK_ERROR

    if(!H5F_addr_defined(fs_addr))
        TEST_ERROR
    if (frsp->nclasses != nclasses)
	TEST_ERROR

    HDmemset(&state, 0, sizeof(frspace_state_t));
    if(check_stats(f, frsp, &state))
        TEST_ERROR

    HDmemset(&test_cparam, 0, sizeof(H5FS_create_t));
    if(H5FS_get_cparam_test(frsp, &test_cparam) < 0)
        FAIL_STACK_ERROR
    if (H5FS_cmp_cparam_test(&cparam, &test_cparam))
        FAIL_STACK_ERROR


    if(H5FS_close(f, H5P_DATASET_XFER_DEFAULT, frsp) < 0)
        FAIL_STACK_ERROR
    frsp = NULL;


    if(NULL == (frsp = H5FS_open(f, H5P_DATASET_XFER_DEFAULT, fs_addr,
			nclasses, test_classes, NULL, (hsize_t)FSPACE_THRHD_DEF, (hsize_t)FSPACE_ALIGN_DEF)))
	FAIL_STACK_ERROR

    if(!H5F_addr_defined(fs_addr))
        TEST_ERROR
    if (frsp->nclasses != nclasses)
	TEST_ERROR


    if(H5FS_close(f, H5P_DATASET_XFER_DEFAULT, frsp) < 0)
        FAIL_STACK_ERROR
    frsp = NULL;


    if(H5FS_delete(f, H5P_DATASET_XFER_DEFAULT, fs_addr) < 0)
        FAIL_STACK_ERROR
    fs_addr = HADDR_UNDEF;


    if(H5Fclose(file) < 0)
        FAIL_STACK_ERROR


    if((file_size = h5_get_file_size(filename, fapl)) < 0)
        TEST_ERROR


    if(file_size != empty_size)
        TEST_ERROR

    PASSED()

    return(0);

error:
    H5E_BEGIN_TRY {
        if(frsp)
	    H5FS_close(f, H5P_DATASET_XFER_DEFAULT, frsp);
	H5Fclose(file);
    } H5E_END_TRY;
    return(1);
}
