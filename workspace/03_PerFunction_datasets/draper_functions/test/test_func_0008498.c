fits_write_header(const qfits_header* hdr, const char* fn) {
	FILE* fid;
	fid = fopen(fn, "wb");
	if (!fid) {
		SYSERROR("Failed to open file \"%s\" to write FITS header", fn);
		return -1;
	}
	if (qfits_header_dump(hdr, fid)) {
		ERROR("Failed to write FITS header to file \"%s\"", fn);
		return -1;
	}
	if (fits_pad_file(fid)) {
		ERROR("Failed to pad FITS header to file \"%s\"", fn);
		return -1;
	}
	if (fclose(fid)) {
		SYSERROR("Failed to close file \"%s\" after writing FITS header", fn);
		return -1;
	}
	return 0;
}
