__connman_service_get_default(void)
{
	struct connman_service *service;
	GSequenceIter *iter;

	iter = g_sequence_get_begin_iter(service_list);

	if (g_sequence_iter_is_end(iter) == TRUE)
		return NULL;

	service = g_sequence_get(iter);

	if (is_connected(service) == FALSE)
		return NULL;

	return service;
}
