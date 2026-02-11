cmd_buf_init(void)
{
	unsigned int i, j;
	VCMDBufHead *buf, *b;

	for(i = 0; i < VCMDBS_COUNT; i++)
	{
		VCMDBufData.buffers[i] = NULL;
		VCMDBufData.available[i] = (unsigned int) (vcmdbuf_chunk_size[i] * VCMDBUF_INIT_CHUNK_FACTOR);
		for(j = 0, buf = NULL; j < VCMDBufData.available[i]; j++, buf = b)
		{
			b = v_cmd_buf_allocate(i);
			b->next = buf;
		}
		VCMDBufData.buffers[i] = buf;
	}
	v_cmd_buf_initialized = TRUE;
}
