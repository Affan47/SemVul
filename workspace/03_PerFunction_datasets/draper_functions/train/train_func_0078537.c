ompi_dpm_base_disconnect_waitall (int count, ompi_dpm_base_disconnect_obj **objs)
{

    ompi_request_t **reqs=NULL;
    char *treq=NULL;
    int totalcount = 0;
    int i;
    int ret;

    for (i=0; i<count; i++) {
        if (NULL == objs[i]) {
            printf("Error in comm_disconnect_waitall\n");
            return OMPI_ERROR;
        }

        totalcount += objs[i]->size;
    }

    reqs = (ompi_request_t **) malloc (2*totalcount*sizeof(ompi_request_t *));
    if ( NULL == reqs ) {
        printf("ompi_comm_disconnect_waitall: error allocating memory\n");
        return OMPI_ERROR;
    }


    treq = (char *)reqs;
    for (i=0; i<count; i++) {
        memcpy (treq, objs[i]->reqs, 2*objs[i]->size * sizeof(ompi_request_t *));
        treq += 2*objs[i]->size * sizeof(ompi_request_t *);
    }


    ret = ompi_request_wait_all (2*totalcount, reqs, MPI_STATUSES_IGNORE);


    for (i=0; i< count; i++ ) {
        if (NULL != objs[i]->reqs ) {
            free (objs[i]->reqs );
            free (objs[i]);
        }
    }

    free (reqs);

    return ret;
}
