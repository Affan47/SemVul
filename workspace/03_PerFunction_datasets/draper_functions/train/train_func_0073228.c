screen_add_func(Client *c, int argc, char **argv)
{
	int err = 0;
	Screen *s;

	if (c->state != ACTIVE)
		return 1;

	if (argc != 2) {
		sock_send_error(c->sock, "Usage: screen_add <screenid>\n");
		return 0;
	}

	debug(RPT_DEBUG, "screen_add: Adding screen %s", argv[1]);

	s = client_find_screen(c, argv[1]);
	if (s != NULL) {
		sock_send_error(c->sock, "Screen already exists\n");
		return 0;
	}

	s = screen_create(argv[1], c);
	if (s == NULL) {
		sock_send_error(c->sock, "failed to create screen\n");
		return 0;
	}

	err = client_add_screen(c, s);

	if (err == 0) {
		sock_send_string(c->sock, "success\n");
	} else {
		sock_send_error(c->sock, "failed to add screen\n");
	}
	report(RPT_INFO, "Client on socket %d added added screen \"%s\"", c->sock, s->id);
	return 0;
}
