get_cpu_slab_ptr(struct meminfo *si, int cpu, ulong *cpu_freelist)
{
	ulong cpu_slab_ptr, page, freelist;

	if (cpu_freelist)
		*cpu_freelist = 0;

	switch (vt->cpu_slab_type)
	{
	case TYPE_CODE_STRUCT:
		cpu_slab_ptr = ULONG(si->cache_buf +
                        OFFSET(kmem_cache_cpu_slab) +
			OFFSET(kmem_cache_cpu_page));
		if (cpu_freelist && VALID_MEMBER(kmem_cache_cpu_freelist))
			*cpu_freelist = ULONG(si->cache_buf +
                        	OFFSET(kmem_cache_cpu_slab) +
                        	OFFSET(kmem_cache_cpu_freelist));
		break;

	case TYPE_CODE_ARRAY:
		cpu_slab_ptr = ULONG(si->cache_buf +
			OFFSET(kmem_cache_cpu_slab) + (sizeof(void *)*cpu));

		if (cpu_slab_ptr && cpu_freelist &&
		    VALID_MEMBER(kmem_cache_cpu_freelist)) {
			if (readmem(cpu_slab_ptr + OFFSET(kmem_cache_cpu_freelist),
			    KVADDR, &freelist, sizeof(void *),
			    "kmem_cache_cpu.freelist", RETURN_ON_ERROR))
				*cpu_freelist = freelist;
		}

		if (cpu_slab_ptr && VALID_MEMBER(kmem_cache_cpu_page)) {
			if (!readmem(cpu_slab_ptr + OFFSET(kmem_cache_cpu_page),
			    KVADDR, &page, sizeof(void *),
			    "kmem_cache_cpu.page", RETURN_ON_ERROR))
				cpu_slab_ptr = 0;
			else
				cpu_slab_ptr = page;
		}
		break;

	case TYPE_CODE_PTR:
		cpu_slab_ptr = ULONG(si->cache_buf + OFFSET(kmem_cache_cpu_slab)) +
			kt->__per_cpu_offset[cpu];

		if (cpu_slab_ptr && cpu_freelist &&
		    VALID_MEMBER(kmem_cache_cpu_freelist)) {
			if (readmem(cpu_slab_ptr + OFFSET(kmem_cache_cpu_freelist),
			    KVADDR, &freelist, sizeof(void *),
			    "kmem_cache_cpu.freelist", RETURN_ON_ERROR))
				*cpu_freelist = freelist;
		}

		if (cpu_slab_ptr && VALID_MEMBER(kmem_cache_cpu_page)) {
			if (!readmem(cpu_slab_ptr + OFFSET(kmem_cache_cpu_page),
			    KVADDR, &page, sizeof(void *),
			    "kmem_cache_cpu.page", RETURN_ON_ERROR))
				cpu_slab_ptr = 0;
			else
				cpu_slab_ptr = page;
		}
		break;

	default:
		cpu_slab_ptr = 0;
		error(FATAL, "cannot determine location of kmem_cache.cpu_slab page\n");
	}

	return cpu_slab_ptr;
}
