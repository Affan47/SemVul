add_free_chunk (LOSFreeChunks *free_chunks, size_t size)
{
	size_t num_chunks = size >> LOS_CHUNK_BITS;

	free_chunks->size = size;

	if (num_chunks >= LOS_NUM_FAST_SIZES)
		num_chunks = 0;
	free_chunks->next_size = los_fast_free_lists [num_chunks];
	los_fast_free_lists [num_chunks] = free_chunks;
}
