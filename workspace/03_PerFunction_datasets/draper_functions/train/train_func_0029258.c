ompi_comm_idup_with_info (ompi_communicator_t *comm, ompi_info_t *info, ompi_communicator_t **newcomm, ompi_request_t **req)
{
    struct ompi_comm_idup_with_info_context *context;
    ompi_comm_request_t *request;
    ompi_request_t *subreq;
    int rsize = 0, rc;

    *newcomm = MPI_COMM_NULL;

    request = ompi_comm_request_get ();
    if (NULL == request) {
        return OMPI_ERR_OUT_OF_RESOURCE;
    }

    context = calloc (1, sizeof (*context));
    if (NULL == context) {
        ompi_comm_request_return (request);
        return OMPI_ERR_OUT_OF_RESOURCE;
    }

    context->comm    = comm;
    context->newcomm = newcomm;

    request->context = context;

    rc =  ompi_comm_set_nb (&context->newcomp,
                            comm,
                            comm->c_local_group->grp_proc_count,
                            NULL,
                            rsize,
                            NULL,
                            comm->c_keyhash,
                            comm->error_handler,
                            true,
                            comm->c_local_group,
                            comm->c_remote_group,
                            &subreq);
    if (NULL == context->newcomp) {
        ompi_comm_request_return (request);
        return rc;
    }

    ompi_comm_request_schedule_append (request, ompi_comm_idup_getcid, &subreq, subreq ? 1 : 0);


    *newcomm = context->newcomp;


    ompi_comm_request_start (request);
    *req = &request->super;

    return OMPI_SUCCESS;
}
