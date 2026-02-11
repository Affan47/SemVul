add_with_wraparound(struct ua101 *ua,
				       unsigned int *value, unsigned int add)
{
	*value += add;
	if (*value >= ua->playback.queue_length)
		*value -= ua->playback.queue_length;
}
