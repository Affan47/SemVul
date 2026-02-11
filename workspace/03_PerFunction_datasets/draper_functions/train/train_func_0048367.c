scsi_exit_queue(void)
{
	int i;

	kmem_cache_destroy(scsi_sdb_cache);

	for (i = 0; i < SG_MEMPOOL_NR; i++) {
		struct scsi_host_sg_pool *sgp = scsi_sg_pools + i;
		mempool_destroy(sgp->pool);
		kmem_cache_destroy(sgp->slab);
	}
}
