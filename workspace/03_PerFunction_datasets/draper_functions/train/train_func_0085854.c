mpd_message_feed(struct mpd_message *output, const struct mpd_pair *pair)
{
	if (strcmp(pair->name, "channel") == 0)
		return false;

	if (strcmp(pair->name, "message") == 0) {
		if (output->text != NULL)
			free(output->text);

		output->text = strdup(pair->value);
	}

	return true;
}
