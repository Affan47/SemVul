ompi_comm_request_start (ompi_comm_request_t *request)
{
    opal_mutex_lock (&ompi_comm_request_mutex);
    opal_list_append (&ompi_comm_requests_active, (opal_list_item_t *) request);


    if (!ompi_comm_request_progress_active) {
        opal_progress_register (ompi_comm_request_progress);
        ompi_comm_request_progress_active = true;
    }

    opal_mutex_unlock (&ompi_comm_request_mutex);
}
