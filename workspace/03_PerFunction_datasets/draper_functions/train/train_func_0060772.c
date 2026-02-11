fits_pad_file_with(FILE* fid, char pad) {
	off_t offset;
	int npad;


	offset = ftello(fid);
	npad = (offset % (off_t)FITS_BLOCK_SIZE);
	if (npad) {
		int i;
		npad = FITS_BLOCK_SIZE - npad;
		for (i=0; i<npad; i++)
			if (fwrite(&pad, 1, 1, fid) != 1) {
                SYSERROR("Failed to pad FITS file");
				return -1;
			}
	}
	return 0;
}
