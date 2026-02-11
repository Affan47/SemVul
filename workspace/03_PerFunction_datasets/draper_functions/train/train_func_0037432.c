dm_pool_get_data_dev_size(struct dm_pool_metadata *pmd, dm_block_t *result)
{
	int r = -EINVAL;

	down_read(&pmd->root_lock);
	if (!pmd->fail_io)
		r = dm_sm_get_nr_blocks(pmd->data_sm, result);
	up_read(&pmd->root_lock);

	return r;
}
