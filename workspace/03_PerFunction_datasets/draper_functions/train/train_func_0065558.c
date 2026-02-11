deflate_file_to_buffer_bzip2(server *srv, connection *con, plugin_data *p, unsigned char *start, off_t st_size) {
	bz_stream bz;

	UNUSED(srv);
	UNUSED(con);

	bz.bzalloc = NULL;
	bz.bzfree = NULL;
	bz.opaque = NULL;

	if (BZ_OK != BZ2_bzCompressInit(&bz,
					9,
					0,
					0)) {
		return -1;
	}

	bz.next_in = (char *)start;
	bz.avail_in = st_size;
	bz.total_in_lo32 = 0;
	bz.total_in_hi32 = 0;

	buffer_prepare_copy(p->b, (bz.avail_in * 1.1) + 12);

	bz.next_out = p->b->ptr;
	bz.avail_out = p->b->size;
	bz.total_out_lo32 = 0;
	bz.total_out_hi32 = 0;

	if (BZ_STREAM_END != BZ2_bzCompress(&bz, BZ_FINISH)) {
		BZ2_bzCompressEnd(&bz);
		return -1;
	}


	if (bz.total_out_hi32) return -1;


	p->b->used = bz.total_out_lo32;

	if (BZ_OK != BZ2_bzCompressEnd(&bz)) {
		return -1;
	}

	return 0;
}
