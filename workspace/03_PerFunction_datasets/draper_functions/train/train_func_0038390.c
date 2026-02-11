slurmdb_unpack_cluster_accounting_rec(void **object,
						 uint16_t rpc_version,
						 Buf buffer)
{
	slurmdb_cluster_accounting_rec_t *object_ptr =
		xmalloc(sizeof(slurmdb_cluster_accounting_rec_t));

	*object = object_ptr;

	if(rpc_version >= 5) {
		safe_unpack64(&object_ptr->alloc_secs, buffer);
		safe_unpack32(&object_ptr->cpu_count, buffer);
		safe_unpack64(&object_ptr->down_secs, buffer);
		safe_unpack64(&object_ptr->idle_secs, buffer);
		safe_unpack64(&object_ptr->over_secs, buffer);
		safe_unpack64(&object_ptr->pdown_secs, buffer);
		safe_unpack_time(&object_ptr->period_start, buffer);
		safe_unpack64(&object_ptr->resv_secs, buffer);
	}

	return SLURM_SUCCESS;

unpack_error:
	slurmdb_destroy_cluster_accounting_rec(object_ptr);
	*object = NULL;
	return SLURM_ERROR;
}
