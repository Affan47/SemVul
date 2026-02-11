hpi_dsp_code_read_block(size_t words_requested,
	struct dsp_code *dsp_code, u32 **ppblock)
{
	if (dsp_code->word_count + words_requested > dsp_code->block_length)
		return HPI_ERROR_DSP_FILE_FORMAT;

	*ppblock =
		((u32 *)(dsp_code->pvt->firmware->data)) +
		dsp_code->word_count;
	dsp_code->word_count += words_requested;
	return 0;
}
