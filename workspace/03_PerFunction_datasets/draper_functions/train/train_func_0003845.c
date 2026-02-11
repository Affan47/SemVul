dccoffer_cb (char *word[], void *userdata)
{
	int result;
	struct stat buffer;
	char sum[65];

	result = stat (word[3], &buffer);
	if (result == 0)
	{
		if (buffer.st_size <= (unsigned long long) get_limit () * 1048576)
		{
			sha256_file (word[3], sum);
			hexchat_commandf (ph, "quote PRIVMSG %s :SHA-256 checksum for %s (remote): %s", word[2], word[1], sum);
		}
		else
		{
			hexchat_set_context (ph, hexchat_find_context (ph, NULL, word[3]));
			hexchat_printf (ph, "quote PRIVMSG %s :SHA-256 checksum for %s (remote): (size limit reached, no checksum calculated)", word[2], word[1]);
		}
	}
	else
	{
		hexchat_printf (ph, "File access error!\n");
	}

	return HEXCHAT_EAT_NONE;
}
