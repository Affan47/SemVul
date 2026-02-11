socket_attach_ops(gnutella_socket_t *s,
	enum socket_type type, struct socket_ops *ops, void *owner)
{
	socket_check(s);
	g_assert(!(s->flags & SOCK_F_UDP));
	g_assert(ops != NULL);

	if (NULL == s->resource.tcp)
		WALLOC(s->resource.tcp);

	s->resource.tcp->owner = owner;
	s->resource.tcp->ops = ops;
	s->type = type;
}
