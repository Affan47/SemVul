MMC5BGVROM_BANK1(uint32 A, uint32 V) {
	if (CHRptr[0]) {
		V &= CHRmask1[0]; MMC5BGVPage[(A) >> 10] = &CHRptr[0][(V) << 10] - (A);
	}
}
