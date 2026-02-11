connections_get_new_connection(server *srv) {
	connections *conns = srv->conns;
	size_t i;

	if (conns->size == 0) {
		conns->size = 128;
		conns->ptr = NULL;
		conns->ptr = malloc(sizeof(*conns->ptr) * conns->size);
		for (i = 0; i < conns->size; i++) {
			conns->ptr[i] = connection_init(srv);
		}
	} else if (conns->size == conns->used) {
		conns->size += 128;
		conns->ptr = realloc(conns->ptr, sizeof(*conns->ptr) * conns->size);

		for (i = conns->used; i < conns->size; i++) {
			conns->ptr[i] = connection_init(srv);
		}
	}

	connection_reset(srv, conns->ptr[conns->used]);
#if 0
	fprintf(stderr, "%s.%d: add: ", __FILE__, __LINE__);
	for (i = 0; i < conns->used + 1; i++) {
		fprintf(stderr, "%d ", conns->ptr[i]->fd);
	}
	fprintf(stderr, "\n");
#endif

	conns->ptr[conns->used]->ndx = conns->used;
	return conns->ptr[conns->used++];
}
