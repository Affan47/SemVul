pmemalloc_free(void *pmp, void *ptr_)
{
	struct clump *clp;
	size_t sz;
	int state;
	int i;

	DEBUG("pmp=%lx, ptr_=%lx", pmp, ptr_);

	clp = PMEM(pmp, (struct clump *)((uintptr_t)ptr_ - PMEM_CHUNK_SIZE));


	DEBUG("[0x%lx] clump on: 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx 0x%lx",
			OFF(pmp, clp),
			clp->on[0].off, clp->on[0].ptr_,
			clp->on[1].off, clp->on[1].ptr_,
			clp->on[2].off, clp->on[2].ptr_);

	sz = clp->size & ~PMEM_STATE_MASK;
	state = clp->size & PMEM_STATE_MASK;

	if (state != PMEM_STATE_RESERVED && state != PMEM_STATE_ACTIVE)
		FATAL("freeing clumb in bad state: %d", state);

	if (state == PMEM_STATE_ACTIVE) {


		clp->size = sz | PMEM_STATE_FREEING;
		pmem_persist(clp, sizeof(*clp), 0);
		for (i = 0; i < PMEM_NUM_ON; i++)
			if (clp->on[i].off) {
				uintptr_t *dest =
					PMEM(pmp, (uintptr_t *)clp->on[i].off);
				*dest = (uintptr_t)clp->on[i].ptr_;
				pmem_persist(dest, sizeof(*dest), 0);
			} else
				break;
		for (i = PMEM_NUM_ON - 1; i >= 0; i--)
			clp->on[i].off = 0;
		pmem_persist(clp, sizeof(*clp), 0);
	}
	clp->size = sz | PMEM_STATE_FREE;
	pmem_persist(clp, sizeof(*clp), 0);


	pmemalloc_coalesce_free(pmp);
}
