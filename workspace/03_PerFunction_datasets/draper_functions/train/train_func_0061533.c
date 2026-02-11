linked_fifo_restart(void *p)
{
    struct test_fifo_struct *f = p;
    int retval;


    retval = flags_check_fifo(f);
    if (retval < 0) {
	return retval;
    }


    retval = stat_check_fifo(f);
    if (retval < 0)
	return retval;


    return ring_test_fifo(f);
}
