mergecd32 (uae_u8 *dst, uae_u8 *src, int size)
{
	int i, k;
	k = 0;
	for (i = 0; i < size / 2; i += 2) {
		int j = i + size / 2;
		dst[k + 1] = src[i + 0];
		dst[k + 0] = src[i + 1];
		dst[k + 3] = src[j + 0];
		dst[k + 2] = src[j + 1];
		k += 4;
	}
#if 0
	{
		struct zfile *f;
		f = zfile_fopen ("c:\\d\\1.rom","wb", ZFD_NORMAL);
		zfile_fwrite (dst, 1, size, f);
		zfile_fclose(f);
	}
#endif
}
