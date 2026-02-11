post_aggregator_comm (MPI_Comm comm, int rw_type,
		           int nproc, void *cb_buf,
			   MPI_Datatype *client_comm_dtype_arr,
			   ADIO_Offset *client_comm_sz_arr,
			   MPI_Request **requests_p,
			   int *aggs_client_count_p)
{
    int aggs_client_count = 0;
    MPI_Request *requests;
    int i;

#ifdef DEBUG
    printf ("posting aggregator communication\n");
#endif

    for (i=0; i < nproc; i++)
	if (client_comm_sz_arr[i] > 0)
	    aggs_client_count++;
#ifdef DEBUG
    printf ("aggregator needs to talk to %d clients\n",
	aggs_client_count);
#endif
    *aggs_client_count_p = aggs_client_count;
    if (aggs_client_count) {
	requests = (MPI_Request *)
	    ADIOI_Malloc (aggs_client_count * sizeof(MPI_Request));
	aggs_client_count = 0;
#ifdef AGGREGATION_PROFILE
	MPE_Log_event (5032, 0, NULL);
#endif
	for (i=0; i < nproc; i++) {
	    if (client_comm_sz_arr[i] > 0) {
		if (rw_type == ADIOI_WRITE)
		    MPI_Irecv (cb_buf, 1, client_comm_dtype_arr[i], i,
			       DATA_TAG, comm,
			       &requests[aggs_client_count]);
		else
		    MPI_Isend (cb_buf, 1, client_comm_dtype_arr[i], i,
			       DATA_TAG, comm,
			       &requests[aggs_client_count]);

		aggs_client_count++;
	    }
	}
	*requests_p = requests;
    }
}
