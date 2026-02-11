sample_move_d24_sS (char *dst, jack_default_audio_sample_t *src, unsigned long nsamples, unsigned long dst_skip, dither_state_t *state)
{
        int32_t z;

	while (nsamples--) {
		float_24 (*src, z);
#if __BYTE_ORDER == __LITTLE_ENDIAN
		memcpy (dst, &z, 3);
#elif __BYTE_ORDER == __BIG_ENDIAN
		memcpy (dst, (char *)&z + 1, 3);
#endif
		dst += dst_skip;
		src++;
	}
}
