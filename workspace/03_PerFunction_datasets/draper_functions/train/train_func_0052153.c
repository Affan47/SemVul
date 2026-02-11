cpImage(TIFF* in, TIFF* out, readFunc fin, writeFunc fout,
	uint32 imagelength, uint32 imagewidth, tsample_t spp)
{
	int status = FALSE;
	unsigned char* buf = (unsigned char *)
	    _TIFFmalloc(TIFFRasterScanlineSize(in) * imagelength);
	if (buf) {
		(*fin)(in, buf, imagelength, imagewidth, spp);
		status = (fout)(out, buf, imagelength, imagewidth, spp);
		_TIFFfree(buf);
	}
	return (status);
}
