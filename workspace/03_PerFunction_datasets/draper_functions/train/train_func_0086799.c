skip_input_data (j_decompress_ptr cinfo, long num_bytes)
{
	struct jpeg_source_mgr* src = (struct jpeg_source_mgr*) cinfo->src;

	if (num_bytes > src->bytes_in_buffer)
		{
		ERREXIT(cinfo, JERR_INPUT_EOF);
		}
	else if (num_bytes > 0)
		{
		src->next_input_byte += (size_t) num_bytes;
		src->bytes_in_buffer -= (size_t) num_bytes;
		}
}
