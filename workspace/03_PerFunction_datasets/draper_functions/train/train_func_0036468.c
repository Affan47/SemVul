qidxfile_write_star(qidxfile* qf, int* quads, int nquads) {
	fitsbin_t* fb = qf->fb;
	FILE* fid;
	uint32_t nq;
	int i;
	fitsbin_chunk_t* chunk;

    fid = fitsbin_get_fid(fb);
    chunk = fitsbin_get_chunk(fb, CHUNK_QIDX);


	if (fseeko(fid, fitsbin_get_data_start(fb, chunk) + qf->cursor_index * 2 * sizeof(uint32_t), SEEK_SET)) {
		ERROR("qidxfile_write_star: failed to fseek");
		return -1;
	}
	nq = nquads;
	if (fitsbin_write_item(fb, chunk, &qf->cursor_heap) ||
        fitsbin_write_item(fb, chunk, &nq)) {
		ERROR("qidxfile_write_star: failed to write a qidx offset/size");
		return -1;
	}

	if (fseeko(fid, fitsbin_get_data_start(fb, chunk) + qf->numstars * 2 * sizeof(uint32_t) +
			   qf->cursor_heap * sizeof(uint32_t), SEEK_SET)) {
		SYSERROR("qidxfile_write_star: failed to fseek");
		return -1;
	}

	for (i=0; i<nquads; i++) {

		uint32_t q = quads[i];
        if (fitsbin_write_item(fb, chunk, &q)) {
            ERROR("qidxfile_write_star: failed to write quads");
            return -1;
        }
    }

	qf->cursor_index++;
	qf->cursor_heap += nquads;
	return 0;
}
