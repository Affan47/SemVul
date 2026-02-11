append_to_verify_fifo_(verify_input_fifo *fifo, const FLAC__int32 * const input[], unsigned input_offset, unsigned channels, unsigned wide_samples)
{
	unsigned channel;

	for(channel = 0; channel < channels; channel++)
		memcpy(&fifo->data[channel][fifo->tail], &input[channel][input_offset], sizeof(FLAC__int32) * wide_samples);

	fifo->tail += wide_samples;

	FLAC__ASSERT(fifo->tail <= fifo->size);
}
