snd_pcm_build_linear_format(int width, int pwidth, int unsignd, int big_endian)
{
	if (pwidth == 24) {
		switch (width) {
		case 24:
			width = 0;
			break;
		case 20:
			width = 1;
			break;
		case 18:
			width = 2;
			break;
		default:
			return SND_PCM_FORMAT_UNKNOWN;
		}
		return linear24_formats[width][!!unsignd][!!big_endian];
	} else {
		switch (width) {
		case 8:
			width = 0;
			break;
		case 16:
			width = 1;
			break;
		case 24:
			width = 2;
			break;
		case 32:
			width = 3;
			break;
		default:
			return SND_PCM_FORMAT_UNKNOWN;
		}
		return linear_formats[width][!!unsignd][!!big_endian];
	}
}
