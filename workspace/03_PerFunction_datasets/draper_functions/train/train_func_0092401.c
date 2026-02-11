chanacs_find_host(mychan_t *mychan, const char *host, unsigned int level)
{
	mowgli_node_t *n;
	chanacs_t *ca;

	return_val_if_fail(mychan != NULL && host != NULL, NULL);

	MOWGLI_ITER_FOREACH(n, mychan->chanacs.head)
	{
		ca = (chanacs_t *)n->data;

		if (level != 0x0)
		{
			if ((ca->entity == NULL) && (!match(ca->host, host)) && ((ca->level & level) == level))
				return ca;
		}
		else if ((ca->entity == NULL) && (!match(ca->host, host)))
			return ca;
	}

	return NULL;
}
