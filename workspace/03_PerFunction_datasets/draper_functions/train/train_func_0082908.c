groupacs_find(mygroup_t *mg, myuser_t *mu, unsigned int flags)
{
	mowgli_node_t *n;

	return_val_if_fail(mg != NULL, NULL);
	return_val_if_fail(mu != NULL, NULL);

	MOWGLI_ITER_FOREACH(n, mg->acs.head)
	{
		groupacs_t *ga = n->data;

		if (flags)
		{
			if (ga->mu == mu && ga->mg == mg && (ga->flags & flags))
				return ga;
		}
		else if (ga->mu == mu && ga->mg == mg)
			return ga;
	}

	return NULL;
}
