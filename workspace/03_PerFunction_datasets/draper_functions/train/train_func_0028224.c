fd_flags_restart(void *p)
{
    struct fd_struct **fds = (struct fd_struct **)p;
    int num_tests = sizeof(test_flags)/sizeof(int);
    int i;
    int retval = 0;

    for (i=0; i<num_tests; ++i) {
        retval = check_fd_struct_rdwr(fds[i]);
        if (retval < 0) {
            CRUT_FAIL("Test failed for fd %d (flag 0%o)", fds[i]->fd, test_flags[i]);
	    break;
	}
    }

    return retval;
}
