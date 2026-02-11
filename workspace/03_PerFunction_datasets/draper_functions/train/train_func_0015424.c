__format_metadata(struct dm_cache_metadata *cmd)
{
	int r;

	r = dm_tm_create_with_sm(cmd->bm, CACHE_SUPERBLOCK_LOCATION,
				 &cmd->tm, &cmd->metadata_sm);
	if (r < 0) {
		DMERR("tm_create_with_sm failed");
		return r;
	}

	__setup_mapping_info(cmd);

	r = dm_array_empty(&cmd->info, &cmd->root);
	if (r < 0)
		goto bad;

	dm_disk_bitset_init(cmd->tm, &cmd->discard_info);

	r = dm_bitset_empty(&cmd->discard_info, &cmd->discard_root);
	if (r < 0)
		goto bad;

	cmd->discard_block_size = 0;
	cmd->discard_nr_blocks = 0;

	r = __write_initial_superblock(cmd);
	if (r)
		goto bad;

	cmd->clean_when_opened = true;
	return 0;

bad:
	dm_tm_destroy(cmd->tm);
	dm_sm_destroy(cmd->metadata_sm);

	return r;
}
