init_talloc(struct talloc_chunk *parent,
			 struct talloc_chunk *tc,
			 size_t size, int external)
{
	if (unlikely(tc == NULL))
		return NULL;

	tc->size = size;
	tc->flags = TALLOC_MAGIC;
	if (external)
		tc->flags |= TALLOC_FLAG_EXT_ALLOC;
	tc->destructor = NULL;
	tc->child = NULL;
	tc->name = NULL;
	tc->refs = NULL;

	if (likely(parent)) {
		if (parent->child) {
			parent->child->parent = NULL;
			tc->next = parent->child;
			tc->next->prev = tc;
		} else {
			tc->next = NULL;
		}
		tc->parent = parent;
		tc->prev = NULL;
		parent->child = tc;
	} else {
		tc->next = tc->prev = tc->parent = NULL;
	}

	return TC_PTR_FROM_CHUNK(tc);
}
