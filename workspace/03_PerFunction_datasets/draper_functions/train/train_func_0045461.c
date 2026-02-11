shell_add(struct gnutella_socket *s)
{
	struct gnutella_shell *sh;
	bool granted = FALSE;

	socket_check(s);
	g_assert(0 == s->gdk_tag);
	g_assert(s->getline);

	if (GNET_PROPERTY(shell_debug)) {
		g_debug("%s: incoming shell connection from %s",
			G_STRFUNC, host_addr_port_to_string(s->addr, s->port));
	}

	s->type = SOCK_TYPE_SHELL;
	socket_tos_lowdelay(s);

	sh = shell_new(s);

	if (socket_is_local(s)) {
		granted = shell_grant_local_shell(sh);
	} else {
		granted = shell_grant_remote_shell(sh);
	}

	if (!granted) {
		shell_shutdown(sh);
	}


	shell_handle_event(sh, sh->shutdown ? INPUT_EVENT_W : INPUT_EVENT_RW);
}
