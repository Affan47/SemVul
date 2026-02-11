mca_btl_tcp_endpoint_destruct(mca_btl_tcp_endpoint_t* endpoint)
{
    mca_btl_tcp_proc_remove(endpoint->endpoint_proc, endpoint);
    mca_btl_tcp_endpoint_close(endpoint);
    OBJ_DESTRUCT(&endpoint->endpoint_frags);
    OBJ_DESTRUCT(&endpoint->endpoint_send_lock);
    OBJ_DESTRUCT(&endpoint->endpoint_recv_lock);
}
