empty_output_buffer (j_compress_ptr cinfo) {
	freeimage_dst_ptr dest = (freeimage_dst_ptr) cinfo->dest;

	if (dest->m_io->write_proc(dest->buffer, 1, OUTPUT_BUF_SIZE, dest->outfile) != OUTPUT_BUF_SIZE) {

		jpeg_destroy((j_common_ptr)cinfo);

		JPEG_EXIT((j_common_ptr)cinfo, JERR_FILE_WRITE);
	}

	dest->pub.next_output_byte = dest->buffer;
	dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

	return TRUE;
}
