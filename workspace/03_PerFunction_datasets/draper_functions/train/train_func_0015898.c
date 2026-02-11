_lookup(struct node *const *c, uint32_t key,
			     struct node **p)
{
	*p = NULL;
	while (*c) {
		*p = *c;
		if ((*c)->key == key)
			break;

		if (key < (*c)->key)
			c = &(*c)->l;

		else
			c = &(*c)->r;
	}

	return c;
}
