screen_add_key_func(Client *c, int argc, char **argv)
{
	Screen *s;
	char *id;
	char *keys;

	if (c->state != ACTIVE)
		return 1;

	if (argc != 3) {
		switch (argc) {
			case 1:
				sock_send_error(c->sock, "Usage: screen_add_key <screenid> <keylist>\n");
				break;
			case 2:
				sock_send_error(c->sock, "You must specify a key list\n");
				break;
			default:
				sock_send_error(c->sock, "Too many parameters...\n");
				break;
		}
		return 0;
	}

	id = argv[1];
	keys = argv[2];
	debug(RPT_DEBUG, "screen_add_key: Adding key(s) %s to screen %s", keys, id);


	s = client_find_screen(c, id);
	if (!s) {
		sock_send_error(c->sock, "Unknown screen id\n");
		return 0;
	}


	if (s->keys == NULL) {

		s->keys = strdup(keys);
	}
	else {


		char *new_keys;
		new_keys = realloc(s->keys, strlen(s->keys) + strlen(keys) +1);
		if (new_keys) {
			strcpy(new_keys, s->keys);
			strcat(new_keys, keys);
			free(s->keys);
			s->keys = new_keys;
		}
		else {
			sock_send_error(c->sock, "Could not add new keys\n");
			return 0;
		}
	}

	if (s->keys == NULL)
		sock_send_error(c->sock, "failed\n");
	else
		sock_send_string(c->sock, "success\n");

	return 0;
}
