s0c(FDI *fdi)
{
	int i, bits = (fdi->track_src[0] << 8) | fdi->track_src[1];
	uae_u8 b;
	fdi->track_src += 2;
	bit_drop_next (fdi);
	debuglog ("s0c:bits=%d,data=%s", bits, datalog (fdi->track_src, (bits + 7) / 8));
	while (bits >= 8) {
		byte_mfm_add (fdi, *fdi->track_src++);
		bits -= 8;
	}
	if (bits > 0) {
		i = 7;
		b = *fdi->track_src++;
		while(bits--) {
			bit_mfm_add (fdi, b & (1 << i));
			i--;
		}
	}
}
