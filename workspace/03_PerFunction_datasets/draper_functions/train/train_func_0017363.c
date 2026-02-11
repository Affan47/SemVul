dm_bm_flush(struct dm_block_manager *bm)
{
	if (bm->read_only)
		return -EPERM;

	return dm_bufio_write_dirty_buffers(bm->bufio);
}
