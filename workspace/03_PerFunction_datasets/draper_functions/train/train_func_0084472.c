codefile_write_code(codefile* cf, double* code) {
    fitsbin_chunk_t* chunk = codes_chunk(cf);
    if (fitsbin_write_item(cf->fb, chunk, code)) {
		ERROR("Failed to write code");
		return -1;
	}
	cf->numcodes++;
	return 0;
}
