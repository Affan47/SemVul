error_activity(struct stream *stream, char *received,
				ssize_t bytes)
{
	if (bytes <= 0)
		return FALSE;
	received[bytes] = '\0';
	message("%s", received);
	return TRUE;
}
