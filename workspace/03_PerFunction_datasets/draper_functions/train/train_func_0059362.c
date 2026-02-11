add_call(void (*fptr)(const char *arg), const char *arg)
{
	flist_t	*tmp, *last;

	tmp = last = fhead;

	while (tmp) {
		last = tmp;
		tmp = tmp->next;
	}

	tmp = xmalloc(sizeof(flist_t));

	tmp->fptr = fptr;

	if (arg)
		tmp->arg = xstrdup(arg);
	else
		tmp->arg = NULL;

	tmp->next = NULL;

	if (last)
		last->next = tmp;
	else
		fhead = tmp;
}
