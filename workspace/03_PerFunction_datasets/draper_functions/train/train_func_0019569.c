worker_get_socket(worker_t *self, const char *hostname,
                       const char *portname) {
  socket_t *socket;
  char *tag;
  apr_pool_t *pool;

  apr_pool_create_unmanaged_ex(&pool, NULL, NULL);
  socket =
    apr_hash_get(self->sockets, apr_pstrcat(self->pbody, hostname, portname,
	                                    NULL),
	         APR_HASH_KEY_STRING);

  if (!socket) {
    socket = apr_pcalloc(self->pbody, sizeof(*socket));
    socket->config = apr_hash_make(self->pbody);
    socket->socket_state = SOCKET_CLOSED;
    tag = apr_pstrdup(self->pbody, portname);
    apr_hash_set(self->sockets, apr_pstrcat(self->pbody, hostname, tag,
	                                    NULL),
	         APR_HASH_KEY_STRING, socket);
  }

  self->socket = socket;
  apr_pool_destroy(pool);
}
