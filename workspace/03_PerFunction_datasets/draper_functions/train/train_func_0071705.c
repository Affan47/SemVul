check_node_depth(H5B2_t *bt2, hid_t dxpl, hsize_t record, unsigned depth)
{
    int         rec_depth;

    if((rec_depth = H5B2_get_node_depth_test(bt2, dxpl, &record)) < 0)
        FAIL_STACK_ERROR
    if((unsigned)rec_depth != depth)
        TEST_ERROR


    return(0);

error:
    return(-1);
}
