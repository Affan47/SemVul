handle_fake_recv_function(conString *string, const char *world,
    const char *flags)
{
    Sock *sock;
    int raw = 0;
    const char *p;

    for (p = flags; *p; p++) {
	switch (*p) {
	case 'r': raw = 1; break;
	default:
	    eprintf("invalid flag %c", *p);
	    return 0;
	}
    }

    sock = (!world || !*world) ? xsock : find_sock(world);
    if (!sock ||
	sock->constate <= SS_CONNECTING || sock->constate >= SS_ZOMBIE)
    {
        eprintf("no open world %s", world ? world : "");
	return 0;
    }
    if (raw)
	handle_socket_input(string->data, string->len);
    else
	queue_socket_line(sock, string, 0, 0);
    return 1;
}
