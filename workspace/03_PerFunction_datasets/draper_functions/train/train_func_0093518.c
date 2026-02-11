http_client_on_message_complete(struct http_parser *p) {

	struct http_client *c = p->data;


	if(c->parser.http_major == 1 && c->parser.http_minor == 1) {
		c->keep_alive = 1;
	}
	c->http_version = c->parser.http_minor;

	if(p->upgrade && c->w->s->cfg->websockets) {
		c->is_websocket = 1;
		return 0;
	}


	if(c->path_sz == 1 && *c->path == '/' && c->w->s->cfg->default_root) {
		free(c->path);
		c->path = strdup(c->w->s->cfg->default_root);
		c->path_sz = strlen(c->path);
	}


	worker_process_client(c);
	http_client_reset(c);

	return 0;
}
