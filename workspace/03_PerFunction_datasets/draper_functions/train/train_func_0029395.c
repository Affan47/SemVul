setprg2r(int r, uint32 A, uint32 V) {
	V &= PRGmask2[r];
	setpageptr(2, A, PRGptr[r] ? (&PRGptr[r][V << 11]) : 0, PRGram[r]);
}
