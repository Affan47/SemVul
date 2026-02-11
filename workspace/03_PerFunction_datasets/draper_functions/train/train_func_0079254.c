display_crc_ctl_parse(struct drm_device *dev, char *buf, size_t len)
{
#define N_WORDS 3
	int n_words;
	char *words[N_WORDS];
	enum pipe pipe;
	enum intel_pipe_crc_object object;
	enum intel_pipe_crc_source source;

	n_words = display_crc_ctl_tokenize(buf, words, N_WORDS);
	if (n_words != N_WORDS) {
		DRM_DEBUG_DRIVER("tokenize failed, a command is %d words\n",
				 N_WORDS);
		return -EINVAL;
	}

	if (display_crc_ctl_parse_object(words[0], &object) < 0) {
		DRM_DEBUG_DRIVER("unknown object %s\n", words[0]);
		return -EINVAL;
	}

	if (display_crc_ctl_parse_pipe(words[1], &pipe) < 0) {
		DRM_DEBUG_DRIVER("unknown pipe %s\n", words[1]);
		return -EINVAL;
	}

	if (display_crc_ctl_parse_source(words[2], &source) < 0) {
		DRM_DEBUG_DRIVER("unknown source %s\n", words[2]);
		return -EINVAL;
	}

	return pipe_crc_set_source(dev, pipe, source);
}
