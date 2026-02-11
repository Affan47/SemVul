fill_input_buffer (j_decompress_ptr cinfo)
{
	InputSource_src_ptr src = (InputSource_src_ptr) cinfo->src;
	size_t nbytes;

	nbytes = src->jpeg_provider->input_source->read (src->buffer, INPUT_BUF_SIZE);

	if (nbytes <= 0)
	{
		if (src->start_of_file)
			ERREXIT(cinfo, JERR_INPUT_EMPTY);
		WARNMS(cinfo, JWRN_JPEG_EOF);

		src->buffer[0] = (JOCTET) 0xFF;
		src->buffer[1] = (JOCTET) JPEG_EOI;
		nbytes = 2;
	}
	src->pub.next_input_byte = src->buffer;
	src->pub.bytes_in_buffer = nbytes;
	src->start_of_file = FALSE;

	return TRUE;
}
