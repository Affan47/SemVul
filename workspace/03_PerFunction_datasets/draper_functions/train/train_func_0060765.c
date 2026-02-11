dm_cache_metadata_set_read_write(struct dm_cache_metadata *cmd)
{
	WRITE_LOCK_VOID(cmd);
	dm_bm_set_read_write(cmd->bm);
	WRITE_UNLOCK(cmd);
}
