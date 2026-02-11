close_listener(Listener *l)
{
    if (l->read_ev) {
	EventTcp_CancelPending(l->read_ev);
	l->read_ev = NULL;
    }
    if (l->write_ev) {
	EventTcp_CancelPending(l->write_ev);
	l->write_ev = NULL;
    }
    l->msg[0] = 0;
    if (l->fd >= 0) {
	close(l->fd);
	l->fd = -1;
    }
}
