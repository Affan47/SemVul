gen_l4_btree2(const char *filename, hid_t fapl, const H5B2_create_t *cparam,
    haddr_t *bt2_addr, const hsize_t *records)
{
    hid_t	file = -1;
    H5F_t	*f = NULL;
    hid_t       dxpl = H5P_DATASET_XFER_DEFAULT;
    H5B2_t      *bt2 = NULL;
    hsize_t     record;
    unsigned    u;
    H5B2_stat_t bt2_stat;


    if((file = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0)
        STACK_ERROR


    if(NULL == (f = (H5F_t *)H5I_object(file)))
        STACK_ERROR


    if(create_btree(f, dxpl, cparam, &bt2, bt2_addr) < 0)
        TEST_ERROR


    for(u = 0; u < INSERT_MANY; u++) {
        record = records[u];
        if(H5B2_insert(bt2, dxpl, &record) < 0)
            FAIL_STACK_ERROR
    }


    if(H5B2_stat_info(bt2, &bt2_stat) < 0)
        FAIL_STACK_ERROR
    if(bt2_stat.depth != 4)
        TEST_ERROR


    if(H5B2_close(bt2, dxpl) < 0)
        FAIL_STACK_ERROR
    bt2 = NULL;


    if(H5Fclose(file) < 0)
        STACK_ERROR

    return 0;

error:
    H5E_BEGIN_TRY {
        if(bt2)
            H5B2_close(bt2, dxpl);
	H5Fclose(file);
    } H5E_END_TRY;

    return 1;
}
