mark_pinned_objects_in_block (MSBlockInfo *block, SgenGrayQueue *queue)
{
	int i;
	int last_index = -1;

	if (!block->pin_queue_num_entries)
		return;

	block->has_pinned = TRUE;

	for (i = 0; i < block->pin_queue_num_entries; ++i) {
		int index = MS_BLOCK_OBJ_INDEX (block->pin_queue_start [i], block);
		SGEN_ASSERT (9, index >= 0 && index < MS_BLOCK_FREE / block->obj_size, "invalid object %p index %d max-index %d", block->pin_queue_start [i], index, MS_BLOCK_FREE / block->obj_size);
		if (index == last_index)
			continue;
		MS_MARK_OBJECT_AND_ENQUEUE_CHECKED (MS_BLOCK_OBJ (block, index), block, queue);
		last_index = index;
	}
}
