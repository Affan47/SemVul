ompi_comm_request_free (struct ompi_request_t **ompi_req)
{
    ompi_comm_request_t *request = (ompi_comm_request_t *) *ompi_req;

    if (!(*ompi_req)->req_complete) {
        return MPI_ERR_REQUEST;
    }

    (*ompi_req)->req_complete = false;
    ompi_comm_request_return (request);

    *ompi_req = MPI_REQUEST_NULL;

    return OMPI_SUCCESS;
}
