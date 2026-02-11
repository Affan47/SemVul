cavan_event_get_keylayout_pathname(struct cavan_event_device *dev, char *pathname)
{
	int i;
	char *filename;
	const char *filenames[] =
	{dev->name, "Generic", "qwerty"};

	filename = text_copy(pathname, "/system/usr/keylayout/");
	for (i = 0; i < (int) NELEM(filenames); i++)
	{
		sprintf(filename, "%s.kl", filenames[i]);
		if (access(pathname, R_OK) == 0)
		{
			return pathname;
		}
	}

	return NULL;
}
