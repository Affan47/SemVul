get_resolv_nameservers(list_t *servers, const char *def_port)
{
	char	line[512];


	FILE *f = fopen(RESOLV_FILE, "r");


	if (f == NULL) {
		return KNOT_ENOENT;
	}


	while (fgets(line, sizeof(line), f) != NULL) {
		size_t len;
		char   *pos = line;
		char   *option, *value;


		len = strspn(pos, SEP_CHARS);
		pos += len;


		option = pos;


		len = strcspn(pos, SEP_CHARS);
		pos += len;


		if (len == 0) {
			continue;
		}


		len = strspn(pos, SEP_CHARS);
		pos += len;


		if (len == 0) {
			continue;
		}


		value = strndup(pos, strcspn(pos, SEP_CHARS));


		if (strncmp(option, "nameserver", strlen("nameserver")) == 0) {
			srv_info_t *server;

			server = parse_nameserver(value, def_port);


			if (server != NULL) {
				add_tail(servers, (node_t *)server);
			}
		}


		free(value);
	}


	fclose(f);


	return list_size(servers);
}
