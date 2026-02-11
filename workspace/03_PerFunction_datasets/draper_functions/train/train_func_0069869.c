main(void)
{
    unsigned nerrors = 0;
    hid_t fid = -1;


    puts("Testing the metadata accumulator");


    if((fid = H5Fcreate(FILENAME, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT)) < 0) FAIL_STACK_ERROR


    if(NULL == (f = (H5F_t *)H5I_object(fid))) FAIL_STACK_ERROR


    if(H5FD_set_eoa(f->shared->lf, H5FD_MEM_DEFAULT, (haddr_t)(1024*1024*10)) < 0) FAIL_STACK_ERROR


    if(accum_reset() < 0) FAIL_STACK_ERROR


    nerrors += test_write_read();
    nerrors += test_write_read_nonacc_front();
    nerrors += test_write_read_nonacc_end();
    nerrors += test_accum_overlap();
    nerrors += test_accum_overlap_clean();
    nerrors += test_accum_overlap_size();
    nerrors += test_accum_non_overlap_size();
    nerrors += test_accum_adjust();
    nerrors += test_read_after();
    nerrors += test_free();
    nerrors += test_big();
    nerrors += test_random_write();


    if(H5Fclose(fid) < 0) TEST_ERROR
    HDremove(FILENAME);

    if(nerrors)
        goto error;
    puts("All metadata accumulator tests passed.");

    return 0;

error:
    puts("*** TESTS FAILED ***");
    return 1;
}
