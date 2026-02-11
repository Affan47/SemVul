__cleancache_init_shared_fs(struct super_block *sb)
{
	int pool_id = CLEANCACHE_NO_BACKEND_SHARED;

	if (cleancache_ops) {
		pool_id = cleancache_ops->init_shared_fs(sb->s_uuid, PAGE_SIZE);
		if (pool_id < 0)
			pool_id = CLEANCACHE_NO_POOL;
	}
	sb->cleancache_poolid = pool_id;
}
