irc_convert_out(irc_private_t *j, char *recipient, const char *line) {
	char *recoded;
	recoded_channels_t *r_channel;

	if ((j->recoded_channels)) {

		char *channame = (!xstrncasecmp(recipient, IRC4, 4)) ? recipient+4 : recipient;
		if ((r_channel = irc_find_recode_channel(j->recoded_channels, channame))) {
			if ((recoded = ekg_convert_string_p(line, r_channel->recode->conv_out)))
				return recoded;
		}
	}


	if (j->conv_out == (void *) -1)
		return NULL;

	if (!(recoded = ekg_convert_string_p(line, j->conv_out)))
		debug_error("[irc] ekg_convert_string_p() failed [%x] using not recoded text\n", j->conv_out);

	return recoded;
}
