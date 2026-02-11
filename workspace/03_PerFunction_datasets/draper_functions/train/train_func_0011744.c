snd_pcm_format_value(const char* name)
{
	snd_pcm_format_t format;
	for (format = 0; format <= SND_PCM_FORMAT_LAST; format++) {
		if (snd_pcm_format_names[format] &&
		    strcasecmp(name, snd_pcm_format_names[format]) == 0) {
			return format;
		}
		if (snd_pcm_format_aliases[format] &&
		    strcasecmp(name, snd_pcm_format_aliases[format]) == 0) {
			return format;
		}
	}
	for (format = 0; format <= SND_PCM_FORMAT_LAST; format++) {
		if (snd_pcm_format_descriptions[format] &&
		    strcasecmp(name, snd_pcm_format_descriptions[format]) == 0) {
			return format;
		}
	}
	return SND_PCM_FORMAT_UNKNOWN;
}
