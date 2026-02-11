client_read(const char *filename, int in_server, int flag)
{
	const char *p;
	RADCLIENT *c;
	CONF_SECTION *cs;
	char buffer[256];

	if (!filename) return NULL;

	cs = cf_file_read(filename);
	if (!cs) return NULL;

	c = client_parse(cf_section_sub_find(cs, "client"), in_server);

	p = strrchr(filename, FR_DIR_SEP);
	if (p) {
		p++;
	} else {
		p = filename;
	}

	if (!flag) return c;


	ip_ntoh(&c->ipaddr, buffer, sizeof(buffer));
	if (strcmp(p, buffer) != 0) {
		DEBUG("Invalid client definition in %s: IP address %s does not match name %s", filename, buffer, p);
		client_free(c);
		return NULL;
	}


	return c;
}
