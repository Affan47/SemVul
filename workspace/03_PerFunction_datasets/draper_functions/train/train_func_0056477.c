test_remove_level1_collapse(hid_t fapl, const H5B2_create_t *cparam,
    const bt2_test_param_t *tparam)
{
    hid_t	file = -1;
    H5F_t	*f = NULL;
    hid_t       dxpl = H5P_DATASET_XFER_DEFAULT;
    H5B2_t      *bt2 = NULL;
    haddr_t     bt2_addr;
    hsize_t     record;
    hsize_t     rrecord;
    hsize_t     nrec;
    haddr_t     root_addr;
    H5B2_node_info_test_t ninfo;
    unsigned    u;

    TESTING("B-tree remove: collapse level-1 B-tree back to level-0");


    if(create_file(&file, &f, fapl) < 0)
        TEST_ERROR


    if(create_btree(f, dxpl, cparam, &bt2, &bt2_addr) < 0)
        TEST_ERROR


    for(u = 0; u < INSERT_SPLIT_ROOT_NREC; u++) {
        record = u;
        if(H5B2_insert(bt2, dxpl, &record) < 0)
            FAIL_STACK_ERROR
    }


    ninfo.depth = 1;
    ninfo.nrec = 1;
    record = 31;
    if(check_node_info(bt2, dxpl, record, &ninfo) < 0)
        TEST_ERROR


    if(H5B2_get_nrec(bt2, &nrec) < 0)
        FAIL_STACK_ERROR


    if(nrec != INSERT_SPLIT_ROOT_NREC)
        TEST_ERROR


    if(H5B2_get_root_addr_test(bt2, &root_addr) < 0)
        FAIL_STACK_ERROR


    if(!H5F_addr_defined(root_addr))
        TEST_ERROR


    if(reopen_btree(f, dxpl, &bt2, bt2_addr, tparam) < 0)
        TEST_ERROR


    for(u = 0; u < 14; u++) {
        record = INSERT_SPLIT_ROOT_NREC - (u + 1);
        rrecord = HSIZET_MAX;
        if(H5B2_remove(bt2, dxpl, &record, remove_cb, &rrecord) < 0)
            FAIL_STACK_ERROR


        if(rrecord != (INSERT_SPLIT_ROOT_NREC - (u + 1)))
            TEST_ERROR


        if(H5B2_get_nrec(bt2, &nrec) < 0)
            FAIL_STACK_ERROR


        if(nrec != (INSERT_SPLIT_ROOT_NREC - (u + 1)))
            TEST_ERROR
    }


    ninfo.depth = 0;
    ninfo.nrec = INSERT_SPLIT_ROOT_NREC - u;
    record = 31;
    if(check_node_info(bt2, dxpl, record, &ninfo) < 0)
        TEST_ERROR


    if(H5B2_get_nrec(bt2, &nrec) < 0)
        FAIL_STACK_ERROR


    if(nrec != (INSERT_SPLIT_ROOT_NREC - u))
        TEST_ERROR


    if(H5B2_get_root_addr_test(bt2, &root_addr) < 0)
        FAIL_STACK_ERROR


    if(!H5F_addr_defined(root_addr))
        TEST_ERROR


    if(H5B2_close(bt2, dxpl) < 0)
        FAIL_STACK_ERROR
    bt2 = NULL;


    if(H5Fclose(file) < 0)
        TEST_ERROR

    PASSED();

    return 0;

error:
    H5E_BEGIN_TRY {
        if(bt2)
            H5B2_close(bt2, dxpl);
	H5Fclose(file);
    } H5E_END_TRY;
    return 1;
}
