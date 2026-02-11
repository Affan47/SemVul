list_create (ListDelF f)
{
	List l;

	if (!(l = list_alloc()))
		return(lsd_nomem_error(__FILE__, __LINE__, "list create"));

	l->head = NULL;
	l->tail = &l->head;
	l->iNext = NULL;
	l->fDel = f;
	l->count = 0;
	list_mutex_init(&l->mutex);
	assert(l->magic = LIST_MAGIC);

	return l;
}
