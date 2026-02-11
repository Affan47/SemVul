biovec_init_slabs(void)
{
	int i;

	for (i = 0; i < BIOVEC_NR_POOLS; i++) {
		int size;
		struct biovec_slab *bvs = bvec_slabs + i;

		if (bvs->nr_vecs <= BIO_INLINE_VECS) {
			bvs->slab = NULL;
			continue;
		}

		size = bvs->nr_vecs * sizeof(struct bio_vec);
		bvs->slab = kmem_cache_create(bvs->name, size, 0,
                                SLAB_HWCACHE_ALIGN|SLAB_PANIC, NULL);
	}
}
