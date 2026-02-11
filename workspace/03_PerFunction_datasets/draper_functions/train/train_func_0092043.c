print_separator(char **buf, size_t *len)
{
	int written;

	written = snprintf(*buf, *len, ", ");
	if (written < 0 || written >= *len)
	{
		return FALSE;
	}
	*buf += written;
	*len -= written;
	return TRUE;
}
