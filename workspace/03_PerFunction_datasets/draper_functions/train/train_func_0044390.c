fits_write_i16_image(const int16_t* img, int nx, int ny, const char* fn) {
	int rtn;
    qfitsdumper qoutimg;
    memset(&qoutimg, 0, sizeof(qoutimg));
    qoutimg.filename = fn;
    qoutimg.npix = nx * ny;
    qoutimg.ptype = PTYPE_INT16;
    qoutimg.vbuf = img;
    qoutimg.out_ptype = BPP_16_SIGNED;
	rtn = fits_write_header_and_image(NULL, &qoutimg, nx);
	if (rtn)
		ERROR("Failed to write FITS image to file \"%s\"", fn);
	return rtn;
}
