sst_mem_block_dummy_read(struct sst_mem_block *block)
{
	u32 size;
	u8 tmp_buf[4];
	struct sst_dsp *sst = block->dsp;

	size = block->size > 4 ? 4 : block->size;
	memcpy_fromio(tmp_buf, sst->addr.lpe + block->offset, size);
}
