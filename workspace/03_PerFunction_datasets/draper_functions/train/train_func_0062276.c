ompi_dpm_base_disconnect_init ( ompi_communicator_t *comm)
{
    ompi_dpm_base_disconnect_obj *obj=NULL;
    int ret;
    int i;

    obj = (ompi_dpm_base_disconnect_obj *) calloc(1,sizeof(ompi_dpm_base_disconnect_obj));
    if ( NULL == obj ) {
        printf("Could not allocate disconnect object\n");
        return NULL;
    }

    if ( OMPI_COMM_IS_INTER(comm) ) {
        obj->size = ompi_comm_remote_size (comm);
    } else {
        obj->size = ompi_comm_size (comm);
    }

    obj->comm = comm;
    obj->reqs = (ompi_request_t **) malloc(2*obj->size*sizeof(ompi_request_t *));
    if ( NULL == obj->reqs ) {
        printf("Could not allocate request array for disconnect object\n");
        free (obj);
        return NULL;
    }


    for ( i=0; i < obj->size; i++ ) {
        ret = MCA_PML_CALL(irecv (&(obj->buf), 0, MPI_INT, i,
                     OMPI_COMM_BARRIER_TAG, comm,
                     &(obj->reqs[2*i])));

        if ( OMPI_SUCCESS != ret ) {
            printf("dpm_base_disconnect_init: error %d in irecv to process %d\n", ret, i);
            free (obj->reqs);
            free (obj);
            return NULL;
        }
        ret = MCA_PML_CALL(isend (&(obj->buf), 0, MPI_INT, i,
                     OMPI_COMM_BARRIER_TAG,
                     MCA_PML_BASE_SEND_SYNCHRONOUS,
                     comm, &(obj->reqs[2*i+1])));

        if ( OMPI_SUCCESS != ret ) {
            printf("dpm_base_disconnect_init: error %d in isend to process %d\n", ret, i);
            free (obj->reqs);
            free (obj);
            return NULL;
        }
    }


    return obj;
}
