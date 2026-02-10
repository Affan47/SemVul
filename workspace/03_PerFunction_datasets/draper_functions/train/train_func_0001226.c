chirp_volume_open(const char *volume, time_t stoptime)
{
	struct chirp_volume *v;
	char filename[CHIRP_PATH_MAX];
	char *buffer;
	char *name;
	char *c;
	int result;

	debug(D_MULTI, "opening volume %s", volume);


	c = strchr(volume, '@');
	if(!c) {
		errno = ENOENT;
		return 0;
	}

	v = xxmalloc(sizeof(*v));
	strcpy(v->name, volume);


	strcpy(v->host, v->name);
	c = strchr(v->host, '@');


	strcpy(v->root, c);
	*c = 0;


	for(c = v->root; *c; c++) {
		if(*c == '@')
			*c = '/';
	}


	sprintf(filename, "%s/key", v->root);
	result = chirp_reli_getfile_buffer(v->host, filename, &buffer, stoptime);
	if(result < 0) {
		debug(D_CHIRP, "couldn't open %s: %s", filename, strerror(errno));
		free(v);
		errno = ENOENT;
		return 0;
	}
	strcpy(v->key, buffer);
	string_chomp(v->key);
	free(buffer);


	sprintf(filename, "%s/hosts", v->root);
	result = chirp_reli_getfile_buffer(v->host, filename, &buffer, stoptime);
	if(result < 0) {
		debug(D_CHIRP, "couldn't open %s: %s", filename, strerror(errno));
		free(v);
		errno = ENOENT;
		return 0;
	}


	int maxservers = 0;
	for(c = buffer; *c; c++)
		if(isspace((int) *c))
			maxservers++;


	v->servers = malloc(sizeof(struct chirp_server *) * maxservers);
	v->nservers = 0;
	debug(D_MULTI, "estimating %d servers", maxservers);


	name = strtok(buffer, " \t\n");
	while(name) {
		debug(D_MULTI, "server: %s", name);
		struct chirp_server *s = xxmalloc(sizeof(*s));
		strcpy(s->name, name);
		s->priority = 0;
		s->prepared = 0;
		v->servers[v->nservers++] = s;
		name = strtok(0, " \t\n");
	}


	int i;
	int n = rand() % v->nservers;
	for(i = 0; i < n; i++)
		v->servers[i]->priority++;

	free(buffer);

	return v;
}
