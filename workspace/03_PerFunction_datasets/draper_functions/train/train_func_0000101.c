ADIOI_Complete_async(int *error_code)
{


    ADIO_Status status;
    ADIO_Request *request;
    ADIOI_Async_node *tmp;

    if (!ADIOI_Async_list_head) *error_code = MPI_SUCCESS;
    while (ADIOI_Async_list_head) {
	request = ADIOI_Async_list_head->request;
	(*request)->queued = -1;


	switch ((*request)->optype) {
	case ADIOI_READ:


	    ADIO_ReadComplete(request, &status, error_code);
	    break;
	case ADIOI_WRITE:


	    ADIO_WriteComplete(request, &status, error_code);
	    break;
	default:
	    FPRINTF(stderr, "Error in ADIOI_Complete_Async\n");
	    break;
	}
	(*request)->queued = 0;


	tmp = ADIOI_Async_list_head;
	ADIOI_Async_list_head = ADIOI_Async_list_head->next;
	ADIOI_Free_async_node(tmp);
    }
    ADIOI_Async_list_tail = NULL;
}
