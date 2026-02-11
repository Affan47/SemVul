tomoyo_domain_def(const unsigned char *buffer)
{
	const unsigned char *cp;
	int len;
	if (*buffer != '<')
		return false;
	cp = strchr(buffer, ' ');
	if (!cp)
		len = strlen(buffer);
	else
		len = cp - buffer;
	if (buffer[len - 1] != '>' ||
	    !tomoyo_correct_word2(buffer + 1, len - 2))
		return false;
	return true;
}
