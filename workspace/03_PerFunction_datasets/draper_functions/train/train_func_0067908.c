magnet_set_dht(struct magnet_resource *res, bool dht_support)
{
	g_return_if_fail(res);

	res->dht = booleanize(dht_support);
}
