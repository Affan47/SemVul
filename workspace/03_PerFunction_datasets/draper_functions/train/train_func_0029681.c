__insert(struct dm_thin_device *td, dm_block_t block,
		    dm_block_t data_block)
{
	int r, inserted;
	__le64 value;
	struct dm_pool_metadata *pmd = td->pmd;
	dm_block_t keys[2] = { td->id, block };

	value = cpu_to_le64(pack_block_time(data_block, pmd->time));
	__dm_bless_for_disk(&value);

	r = dm_btree_insert_notify(&pmd->info, pmd->root, keys, &value,
				   &pmd->root, &inserted);
	if (r)
		return r;

	td->changed = 1;
	if (inserted)
		td->mapped_blocks++;

	return 0;
}
