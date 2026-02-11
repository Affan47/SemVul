plug_proxy_accepting (Plug p, OSSocket sock)
{
    Proxy_Plug pp = (Proxy_Plug) p;
    Proxy_Socket ps = pp->proxy_socket;

    if (ps->state != PROXY_STATE_ACTIVE) {
	ps->accepting_sock = sock;
	return ps->negotiate(ps, PROXY_CHANGE_ACCEPTING);
    }
    return plug_accepting(ps->plug, sock);
}
