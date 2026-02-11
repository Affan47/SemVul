hattach(void * block, void * parent)
{
	hblock_t * b, * p;

	if (! block)
	{
		assert(! parent);
		return;
	}


	b = structof(block, hblock_t, data);
	assert(b->magic == HH_MAGIC);

	hlist_del(&b->siblings);

	if (! parent)
		return;


	p = structof(parent, hblock_t, data);
	assert(p->magic == HH_MAGIC);


	assert(b != p);
	assert(! _relate(p, b));

	hlist_add(&p->children, &b->siblings);
}
