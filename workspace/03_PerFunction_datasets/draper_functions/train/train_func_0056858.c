scsi_put_host_cmd_pool(struct Scsi_Host *shost)
{
	struct scsi_host_template *hostt = shost->hostt;
	struct scsi_host_cmd_pool *pool;

	mutex_lock(&host_cmd_pool_mutex);
	pool = scsi_find_host_cmd_pool(shost);


	BUG_ON(pool->users == 0);

	if (!--pool->users) {
		kmem_cache_destroy(pool->cmd_slab);
		kmem_cache_destroy(pool->sense_slab);
		if (hostt->cmd_size) {
			scsi_free_host_cmd_pool(pool);
			hostt->cmd_pool = NULL;
		}
	}
	mutex_unlock(&host_cmd_pool_mutex);
}
