read_dns_pipe(void *data, size_t length)
{
	if (read(dns_r_pipe, data, length) != length)
	{
		fprintf(stderr, "gb.net: cannot read DNS pipe: %s\n", strerror(errno));
		return TRUE;
	}

	return FALSE;
}
