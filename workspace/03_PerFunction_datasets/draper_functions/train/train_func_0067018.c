amiga_data (FDI *fdi, uae_u8 *secbuf)
{
	uae_u16 mfmbuf[4 + 512];
	uae_u32 dodd, deven, dck;
	int i;

	for (i = 0; i < 512; i += 4) {
		deven = ((secbuf[i + 0] << 24) | (secbuf[i + 1] << 16)
			| (secbuf[i + 2] << 8) | (secbuf[i + 3]));
		dodd = deven >> 1;
		deven &= 0x55555555;
		dodd &= 0x55555555;
		mfmbuf[(i >> 1) + 4] = (uae_u16) (dodd >> 16);
		mfmbuf[(i >> 1) + 5] = (uae_u16) dodd;
		mfmbuf[(i >> 1) + 256 + 4] = (uae_u16) (deven >> 16);
		mfmbuf[(i >> 1) + 256 + 5] = (uae_u16) deven;
	}
	dck = 0;
	for (i = 4; i < 4 + 512; i += 2)
		dck ^= (mfmbuf[i] << 16) | mfmbuf[i + 1];
	deven = dodd = dck;
	dodd >>= 1;
	deven &= 0x55555555;
	dodd &= 0x55555555;
	mfmbuf[0] = (uae_u16) (dodd >> 16);
	mfmbuf[1] = (uae_u16) dodd;
	mfmbuf[2] = (uae_u16) (deven >> 16);
	mfmbuf[3] = (uae_u16) deven;

	for (i = 0; i < 4 + 512; i ++)
		word_post_mfm_add (fdi, mfmbuf[i]);
}
