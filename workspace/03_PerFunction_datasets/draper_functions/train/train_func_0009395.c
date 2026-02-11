test_man_insert_weird(hid_t fapl, H5HF_create_t *cparam, fheap_test_param_t *tparam)
{
    hid_t	file = -1;
    hid_t       dxpl = H5P_DATASET_XFER_DEFAULT;
    char	filename[FHEAP_FILENAME_LEN];
    H5F_t	*f = NULL;
    H5HF_t      *fh = NULL;
    haddr_t     fh_addr;
    unsigned char heap_id[HEAP_ID_LEN];
    size_t      id_len;
    fheap_heap_state_t state;
    herr_t      ret;


    h5_fixname(FILENAME[0], fapl, filename, sizeof(filename));


    if((file = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0)
        FAIL_STACK_ERROR


    if(NULL == (f = H5I_object(file)))
        FAIL_STACK_ERROR


    if(NULL == (fh = H5HF_create(f, dxpl, cparam)))
        FAIL_STACK_ERROR
    if(H5HF_get_id_len(fh, &id_len) < 0)
        FAIL_STACK_ERROR
    if(id_len > HEAP_ID_LEN)
        TEST_ERROR
    if(H5HF_get_heap_addr(fh, &fh_addr) < 0)
        FAIL_STACK_ERROR
    if(!H5F_addr_defined(fh_addr))
        TEST_ERROR
    HDmemset(&state, 0, sizeof(fheap_heap_state_t));
    if(check_stats(fh, &state))
        TEST_ERROR


    if(reopen_heap(f, dxpl, &fh, fh_addr, tparam) < 0)
        TEST_ERROR


    TESTING("inserting 'weird' sized objects into absolute heap");


    H5E_BEGIN_TRY {
        ret = H5HF_insert(fh, dxpl, (size_t)0, shared_wobj_g, heap_id);
    } H5E_END_TRY;
    if(ret >= 0)
        TEST_ERROR
    H5Eclear2(H5E_DEFAULT);


    if(add_obj(fh, dxpl, (size_t)10, (size_t)1, &state, NULL))
        TEST_ERROR


    if(reopen_heap(f, dxpl, &fh, fh_addr, tparam) < 0)
        TEST_ERROR


    if(check_stats(fh, &state))
        TEST_ERROR


    if(H5HF_close(fh, dxpl) < 0)
        FAIL_STACK_ERROR
    fh = NULL;


    if(H5Fclose(file) < 0)
        FAIL_STACK_ERROR


    PASSED()

    return(0);

error:
    H5E_BEGIN_TRY {
        if(fh)
            H5HF_close(fh, dxpl);
	H5Fclose(file);
    } H5E_END_TRY;
    return(1);
}
