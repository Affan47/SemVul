assoc_elemfree(ASSOCELEM *ep)
{
	int i;

	for (i = 0; i < ep->e_dim; i++)
		freevalue(&ep->e_indices[i]);
	freevalue(&ep->e_value);
	ep->e_dim = 0;
	ep->e_next = NULL;
	free((char *) ep);
}
