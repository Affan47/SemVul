sample_move_dS_s16s (jack_default_audio_sample_t *dst, char *src, unsigned long nsamples, unsigned long src_skip)
{
	short z;


	while (nsamples--) {
#if __BYTE_ORDER == __LITTLE_ENDIAN
		z = (unsigned char)(src[0]);
		z <<= 8;
		z |= (unsigned char)(src[1]);
#elif __BYTE_ORDER == __BIG_ENDIAN
		z = (unsigned char)(src[1]);
		z <<= 8;
		z |= (unsigned char)(src[0]);
#endif
		*dst = z / SAMPLE_16BIT_SCALING;
		dst++;
		src += src_skip;
	}
}
