fitsbin_write_chunk_header_to(fitsbin_t* fb, fitsbin_chunk_t* chunk, FILE* fid) {
	off_t start, end;
    qfits_header* hdr;
    hdr = fitsbin_get_chunk_header(fb, chunk);
    if (fitsfile_write_header(fid, hdr, &start, &end, -1, ""))
        return -1;
	return 0;
}
