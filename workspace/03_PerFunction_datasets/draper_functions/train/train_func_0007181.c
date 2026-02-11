dm_cache_metadata_set_stats(struct dm_cache_metadata *cmd,
				 struct dm_cache_statistics *stats)
{
	WRITE_LOCK_VOID(cmd);
	cmd->stats = *stats;
	WRITE_UNLOCK(cmd);
}
