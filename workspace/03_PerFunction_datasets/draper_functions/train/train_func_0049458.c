dump_error(hid_t estack)
{

    HDfprintf(stderr, "********* Print error stack in HDF5 default way *********\n");
    if(H5Eprint2(estack, stderr) < 0)
        TEST_ERROR;


    HDfprintf(stderr, "\n********* Print error stack in customized way *********\n");
    if(H5Ewalk2(estack, H5E_WALK_UPWARD, custom_print_cb, stderr) < 0)
        TEST_ERROR;

    return 0;

error:
    return -1;
}
