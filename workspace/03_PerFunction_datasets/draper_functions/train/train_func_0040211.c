get_file_content (FILE *stream)
{
	char *buffer;
	ssize_t bytes_read;
	long filesize;
	int res, offset = 0;

	res = fseek (stream, 0, SEEK_END);
	if (res < 0)
	  return NULL;

	filesize = ftell (stream);
	if (filesize < 0)
	  return NULL;

	res = fseek (stream, 0, SEEK_SET);
	if (res < 0)
	  return NULL;

	if (filesize > MAX_FILE_SIZE)
	  return NULL;

	buffer = (char *)g_malloc ((filesize + 1) * sizeof (char));
	while ((bytes_read = fread (buffer + offset, 1, LINE_BUFFER_SIZE, stream)) > 0)
		offset += bytes_read;


	buffer[filesize] = '\0';
	return buffer;
}
