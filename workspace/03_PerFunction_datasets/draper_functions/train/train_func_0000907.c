nickpad_string_create(channel_t *chan)
{
	int i;
	chan->nickpad_len = (chan->longest_nick + 1) * fillchars_len;
	xfree (chan->nickpad_str);
	chan->nickpad_str = (char *)xmalloc(chan->nickpad_len);


	for (i = 0; i < chan->nickpad_len; i++)
		chan->nickpad_str[i] = fillchars[ i % fillchars_len ];

	debug("created NICKPAD with len: %d\n", chan->nickpad_len);
	return chan->nickpad_str;
}
