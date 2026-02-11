extract_content_length(char *buffer, int size)
{
	char *clen = strstr(buffer, CONTENT_LENGTH);
	char *content_buffer = NULL;
	char *buf_len;
	int inc = 0;
	int i;


	buf_len = (char *)MALLOC(40);


	if (!clen)
		return 0;


	while (*(clen++) != ':');
	content_buffer = clen;
	while (*(clen++) != '\r' && *clen != '\n')
		inc++;
	for (i = 0; i < inc; i++)
		strncat(buf_len, content_buffer+i, 1);
	i = atoi(buf_len);
	FREE(buf_len);
	return i;
}
