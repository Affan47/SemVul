sample_move_dS_s24s (jack_default_audio_sample_t *dst, char *src, unsigned long nsamples, unsigned long src_skip)
{


	while (nsamples--) {
		int x;
#if __BYTE_ORDER == __LITTLE_ENDIAN
		x = (unsigned char)(src[0]);
		x <<= 8;
		x |= (unsigned char)(src[1]);
		x <<= 8;
		x |= (unsigned char)(src[2]);

		if (src[0] & 0x80) {
			x |= 0xff << 24;
		}
#elif __BYTE_ORDER == __BIG_ENDIAN
		x = (unsigned char)(src[2]);
		x <<= 8;
		x |= (unsigned char)(src[1]);
		x <<= 8;
		x |= (unsigned char)(src[0]);

		if (src[2] & 0x80) {
			x |= 0xff << 24;
		}
#endif
		*dst = x / SAMPLE_24BIT_SCALING;
		dst++;
		src += src_skip;
	}
}
