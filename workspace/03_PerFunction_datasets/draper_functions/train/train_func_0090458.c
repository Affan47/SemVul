flist_insert_obj(flist *list, void *object, int position)
{
	flist *new;
	flist *tl;

	if (position < 0)
	{
		return flist_append_obj(list, object);
	}
	if (position == 0)
	{
		return flist_prepend_obj(list, object);
	}
	tl = list;
	while(tl && position-- > 0)
	{
		tl = tl->next;
	}

	if (!tl)
	{
		return flist_append_obj(list, object);
	}

	new = (flist *)safemalloc(sizeof(flist));;
	new->object = object;
	new->prev = NULL;

	if (tl->prev)
	{
		tl->prev->next = new;
		new->prev = tl->prev;
	}
	new->next = tl;
	tl->prev = new;

	if (tl == list)
	{
		return new;
	}

	return list;
}
