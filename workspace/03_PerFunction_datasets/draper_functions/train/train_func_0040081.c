mca_btl_sctp_proc_accept(mca_btl_sctp_proc_t* btl_proc, struct sockaddr_in* addr, int sd)
{
    size_t i;
    OPAL_THREAD_LOCK(&btl_proc->proc_lock);
    for(i=0; i<btl_proc->proc_endpoint_count; i++) {
        mca_btl_base_endpoint_t* btl_endpoint = btl_proc->proc_endpoints[i];
        if(mca_btl_sctp_endpoint_accept(btl_endpoint, addr, sd)) {
            OPAL_THREAD_UNLOCK(&btl_proc->proc_lock);
            return true;
        }
    }
    OPAL_THREAD_UNLOCK(&btl_proc->proc_lock);
    return false;
}
