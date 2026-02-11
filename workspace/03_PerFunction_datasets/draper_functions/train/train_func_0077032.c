ompi_io_ompio_unregister_print_entry (int queue_type,
					   print_entry *x){

    int ret = OMPI_SUCCESS;
    print_queue *q=NULL;
    ret = ompi_io_ompio_set_print_queue(&q, queue_type);
    if (ret != OMPI_ERROR){
	if (q->count <= 0){
	    return OMPI_ERROR;
	}
	else{
	    *x = q->entry[q->first];
	    q->first = (q->first+1) % QUEUESIZE;
	    q->count = q->count - 1;
	}
    }
    return OMPI_SUCCESS;
}
