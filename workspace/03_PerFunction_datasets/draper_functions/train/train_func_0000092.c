ompi_io_ompio_full_print_queue(int queue_type){


    int ret = OMPI_SUCCESS;
    print_queue *q=NULL;
    ret =  ompi_io_ompio_set_print_queue(&q, queue_type);

    assert ( ret != OMPI_ERROR);
    if (q->count < QUEUESIZE)
	    return 0;
    else
	return 1;

}
