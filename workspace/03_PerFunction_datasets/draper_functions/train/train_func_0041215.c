alloc_enter(ALLOC *chain)
{
	ALLOC *a = chain->tail ? chain->tail : chain;
	char *entry;

	if (!a->free)
	{
		a = alloc_init(chain->size, chain->nel);
		if (!chain->tail) chain->tail = chain;
		chain->tail->next = a;
		chain->tail = a;
	}

	entry = a->data + (a->nel - a->free) * a->size;
	--a->free;
	return entry;
}
