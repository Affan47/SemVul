read_line(
void *fdata,
int y,
char *dst
) {
	if (TIFFReadScanline((TIFF *)fdata, (tdata_t)dst, y, 0) < 0)
		return 1;
	return 0;
}
