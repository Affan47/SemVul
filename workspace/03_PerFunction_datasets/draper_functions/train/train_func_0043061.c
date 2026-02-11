copyName (tagFile *const file)
{
	size_t length;
	const char *end = strchr (file->line.buffer, '\t');
	if (end == NULL)
	{
		end = strchr (file->line.buffer, '\n');
		if (end == NULL)
			end = strchr (file->line.buffer, '\r');
	}
	if (end != NULL)
		length = end - file->line.buffer;
	else
		length = strlen (file->line.buffer);
	while (length >= file->name.size)
		growString (&file->name);
	strncpy (file->name.buffer, file->line.buffer, length);
	file->name.buffer [length] = '\0';
}
