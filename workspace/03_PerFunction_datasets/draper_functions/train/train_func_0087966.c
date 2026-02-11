bitwriter_grow_(FLAC__BitWriter *bw, unsigned bits_to_add)
{
	unsigned new_capacity;
	uint32_t *new_buffer;

	FLAC__ASSERT(0 != bw);
	FLAC__ASSERT(0 != bw->buffer);


	new_capacity = bw->words + ((bw->bits + bits_to_add + FLAC__BITS_PER_WORD - 1) / FLAC__BITS_PER_WORD);


	if(bw->capacity >= new_capacity)
		return true;


	if((new_capacity - bw->capacity) % FLAC__BITWRITER_DEFAULT_INCREMENT)
		new_capacity += FLAC__BITWRITER_DEFAULT_INCREMENT - ((new_capacity - bw->capacity) % FLAC__BITWRITER_DEFAULT_INCREMENT);

	FLAC__ASSERT(0 == (new_capacity - bw->capacity) % FLAC__BITWRITER_DEFAULT_INCREMENT);
	FLAC__ASSERT(new_capacity > bw->capacity);
	FLAC__ASSERT(new_capacity >= bw->words + ((bw->bits + bits_to_add + FLAC__BITS_PER_WORD - 1) / FLAC__BITS_PER_WORD));

	new_buffer = safe_realloc_mul_2op_(bw->buffer, sizeof(uint32_t), new_capacity);
	if(new_buffer == 0)
		return false;
	bw->buffer = new_buffer;
	bw->capacity = new_capacity;
	return true;
}
