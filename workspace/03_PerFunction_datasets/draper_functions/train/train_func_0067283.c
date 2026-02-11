target_configure_unmap_from_queue(struct se_dev_attrib *attrib,
				       struct request_queue *q)
{
	int block_size = queue_logical_block_size(q);

	if (!blk_queue_discard(q))
		return false;

	attrib->max_unmap_lba_count =
		q->limits.max_discard_sectors >> (ilog2(block_size) - 9);


	attrib->max_unmap_block_desc_count = 1;
	attrib->unmap_granularity = q->limits.discard_granularity / block_size;
	attrib->unmap_granularity_alignment = q->limits.discard_alignment /
								block_size;
	return true;
}
