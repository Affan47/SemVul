operclass_find(const char *name)
{
	operclass_t *operclass;
	mowgli_node_t *n;

	MOWGLI_ITER_FOREACH(n, operclasslist.head)
	{
		operclass = (operclass_t *)n->data;

		if (!strcasecmp(operclass->name, name))
			return operclass;
	}

	return NULL;
}
