block_map(void* blockp, map_func_t func)
{
	int32_t size = TIMG_BLOCK_SIZE;
	struct ByteBlock* real_blockp = (struct ByteBlock*) blockp;

	for (int32_t i=0;i<size*size;i++) {
		int32_t x = i % size;
		int32_t y = i / size;

		func((void *)(&real_blockp->data), x, y);
	}
}
