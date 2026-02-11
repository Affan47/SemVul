rx_link_init(rxdrv_t *rx, const void *args)
{
	const struct rx_link_args *rargs = args;
	struct attr *attr;

	rx_check(rx);
	g_assert(rargs);
	g_assert(rargs->cb);

	WALLOC0(attr);
	attr->cb = rargs->cb;
	attr->wio = rargs->wio;
	attr->bws = rargs->bws;
	attr->bio = NULL;

	rx->opaque = attr;

	return rx;
}
