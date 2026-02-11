sk_proxy_flush (Socket s)
{
    Proxy_Socket ps = (Proxy_Socket) s;

    if (ps->state != PROXY_STATE_ACTIVE) {
	ps->pending_flush = 1;
	return;
    }
    sk_flush(ps->sub_socket);
}
