tan_write_to_file(const tan_t* tan, const char* fn) {
	FILE* fid;
	int res;
	fid = fopen(fn, "wb");
	if (!fid) {
		SYSERROR("Failed to open file \"%s\" to write WCS header", fn);
		return -1;
	}
	res = tan_write_to(tan, fid);
	if (res) {
		ERROR("Failed to write FITS header to file \"%s\"", fn);
		return -1;
	}
	if (fclose(fid)) {
		SYSERROR("Failed to close file \"%s\" after writing WCS header", fn);
		return -1;
	}
	return 0;
}
