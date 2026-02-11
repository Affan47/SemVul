mitm_rs_error(struct mitm_descriptor* desc)
{
    J_CLOSE(&desc->fd[FDMITM]);
    J_BUFFEREVENT_FREE(&desc->mitm_bufferevent);

    event_add(&desc->ev_recv[FDMITMATTACH], NULL);
}
