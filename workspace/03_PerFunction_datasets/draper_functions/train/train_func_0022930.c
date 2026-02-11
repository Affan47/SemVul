snd_pcm_lfloat_get_s32_index(snd_pcm_format_t format)
{
	int width, endian;

	switch (format) {
	case SND_PCM_FORMAT_FLOAT_LE:
	case SND_PCM_FORMAT_FLOAT_BE:
		width = 32;
		break;
	case SND_PCM_FORMAT_FLOAT64_LE:
	case SND_PCM_FORMAT_FLOAT64_BE:
		width = 64;
		break;
	default:
		return -EINVAL;
	}
#ifdef SND_LITTLE_ENDIAN
	endian = snd_pcm_format_big_endian(format);
#else
	endian = snd_pcm_format_little_endian(format);
#endif
	return ((width / 32)-1) * 2 + endian;
}
