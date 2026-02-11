env_undefine(unsigned char *var)
{
	struct env_lst *ep;

	if ((ep = env_find(var))) {
		ep->prev->next = ep->next;
		if (ep->next)
			ep->next->prev = ep->prev;
		if (ep->var)
			free(ep->var);
		if (ep->value)
			free(ep->value);
		free(ep);
	}
}
