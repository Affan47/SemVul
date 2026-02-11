cts_sent(mca_btl_base_module_t* btl,
                     struct mca_btl_base_endpoint_t* ep,
                     struct mca_btl_base_descriptor_t* des,
                     int status)
{


    OPAL_OUTPUT((-1, "CTS send to %s completed",
                 (NULL == ep->endpoint_proc->proc_ompi->proc_hostname) ?
                 "unknown" : ep->endpoint_proc->proc_ompi->proc_hostname));
}
