block_alloc(struct sst_dsp *dsp, struct sst_block_allocator *ba,
	struct list_head *block_list)
{
	struct sst_mem_block *block, *tmp;
	int ret = 0;

	if (ba->size == 0)
		return 0;


	list_for_each_entry_safe(block, tmp, &dsp->free_block_list, list) {


		if (block->type != ba->type)
			continue;

		if (ba->size > block->size)
			continue;

		ba->offset = block->offset;
		block->bytes_used = ba->size % block->size;
		list_add(&block->module_list, block_list);
		list_move(&block->list, &dsp->used_block_list);
		dev_dbg(dsp->dev, "block allocated %d:%d at offset 0x%x\n",
			block->type, block->index, block->offset);
		return 0;
	}


	list_for_each_entry_safe(block, tmp, &dsp->free_block_list, list) {


		if (block->type != ba->type)
			continue;


		if (ba->size > block->size) {


			ba->offset = block->offset;

			ret = block_alloc_contiguous(dsp, ba, block_list);
			if (ret == 0)
				return ret;

		}
	}


	return -ENOMEM;
}
