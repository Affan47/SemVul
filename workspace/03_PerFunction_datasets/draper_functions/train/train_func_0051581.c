dsm_postmaster_startup(PGShmemHeader *shim)
{
	void	   *dsm_control_address = NULL;
	uint32		maxitems;
	Size		segsize;

	Assert(!IsUnderPostmaster);


	if (dynamic_shared_memory_type == DSM_IMPL_NONE)
		return;


	if (dynamic_shared_memory_type == DSM_IMPL_MMAP)
		dsm_cleanup_for_mmap();


	maxitems = PG_DYNSHMEM_FIXED_SLOTS
		+ PG_DYNSHMEM_SLOTS_PER_BACKEND * MaxBackends;
	elog(DEBUG2, "dynamic shared memory system will support %u segments",
		 maxitems);
	segsize = dsm_control_bytes_needed(maxitems);


	for (;;)
	{
		Assert(dsm_control_address == NULL);
		Assert(dsm_control_mapped_size == 0);
		dsm_control_handle = random();
		if (dsm_control_handle == 0)
			continue;
		if (dsm_impl_op(DSM_OP_CREATE, dsm_control_handle, segsize,
						&dsm_control_impl_private, &dsm_control_address,
						&dsm_control_mapped_size, ERROR))
			break;
	}
	dsm_control = dsm_control_address;
	on_shmem_exit(dsm_postmaster_shutdown, PointerGetDatum(shim));
	elog(DEBUG2,
		 "created dynamic shared memory control segment %u (%zu bytes)",
		 dsm_control_handle, segsize);
	shim->dsm_control = dsm_control_handle;


	dsm_control->magic = PG_DYNSHMEM_CONTROL_MAGIC;
	dsm_control->nitems = 0;
	dsm_control->maxitems = maxitems;
}
