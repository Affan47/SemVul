create_boot_cache(struct kmem_cache *s, const char *name, size_t size,
		unsigned long flags)
{
	int err;

	s->name = name;
	s->size = s->object_size = size;
	s->align = calculate_alignment(flags, ARCH_KMALLOC_MINALIGN, size);

	slab_init_memcg_params(s);

	err = __kmem_cache_create(s, flags);

	if (err)
		panic("Creation of kmalloc slab %s size=%zu failed. Reason %d\n",
					name, size, err);

	s->refcount = -1;
}
