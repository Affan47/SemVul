decode(void* raster, u_int w, u_int h)
{
    u_int rowbytes = howmany(w, 8);
    if (curruns == NULL) {
	tiff_runlen_t runs[2*4864];
	setRuns(runs, runs+4864, w);
	while (h-- > 0) {
	    decodeRow(raster, w);
	    if (raster)
		raster = (u_char*) raster + rowbytes;
	}
    } else {
	while (h-- > 0) {
	    decodeRow(raster, w);
	    if (raster)
		raster = (u_char*) raster + rowbytes;
	}
    }
}
