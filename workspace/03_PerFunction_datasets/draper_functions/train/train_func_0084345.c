set_limit (char* size)
{
	int buffer = atoi (size);

	if (buffer > 0 && buffer < INT_MAX)
	{
		if (hexchat_pluginpref_set_int (ph, "limit", buffer))
		{
			hexchat_printf (ph, "File size limit has successfully been set to: %d MiB\n", buffer);
		}
		else
		{
			hexchat_printf (ph, "File access error while saving!\n");
		}
	}
	else
	{
		hexchat_printf (ph, "Invalid input!\n");
	}
}
