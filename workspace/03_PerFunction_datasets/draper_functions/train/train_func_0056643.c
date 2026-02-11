list_at(struct list *l, int nr)
{
	void *retval, *p;
	int i;

	__lock(l);
	for (p = l->l_first, i = 0; p && i < nr; p = *LIST_NEXT_PTR(l, p), i++)
		;
	if (p)
		retval = p;
	else
		retval = NULL;
	__unlock(l);
	return retval;
}
