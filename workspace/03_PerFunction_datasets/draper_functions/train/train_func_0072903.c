jpeg_freeimage_src (j_decompress_ptr cinfo, fi_handle infile, FreeImageIO *io) {
	freeimage_src_ptr src;


	if (cinfo->src == NULL) {
		cinfo->src = (struct jpeg_source_mgr *) (*cinfo->mem->alloc_small)
			((j_common_ptr) cinfo, JPOOL_PERMANENT, sizeof(SourceManager));

		src = (freeimage_src_ptr) cinfo->src;

		src->buffer = (JOCTET *) (*cinfo->mem->alloc_small)
			((j_common_ptr) cinfo, JPOOL_PERMANENT, INPUT_BUF_SIZE * sizeof(JOCTET));
	}


	src = (freeimage_src_ptr) cinfo->src;
	src->pub.init_source = init_source;
	src->pub.fill_input_buffer = fill_input_buffer;
	src->pub.skip_input_data = skip_input_data;
	src->pub.resync_to_restart = jpeg_resync_to_restart;
	src->pub.term_source = term_source;
	src->infile = infile;
	src->m_io = io;
	src->pub.bytes_in_buffer = 0;
	src->pub.next_input_byte = NULL;
}
