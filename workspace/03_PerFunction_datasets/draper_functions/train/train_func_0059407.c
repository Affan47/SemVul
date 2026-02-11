fetch_ref(char *ref, unsigned char *sha1)
{
	signed char remote;
	char type = 'r';
	int length = strlen(ref) + 1;
	if (write_in_full(fd_out, &type, 1) != 1 ||
	    write_in_full(fd_out, ref, length) != length)
		return -1;

	if (read_in_full(fd_in, &remote, 1) != 1)
		return -1;
	if (remote < 0)
		return remote;
	if (read_in_full(fd_in, sha1, 20) != 20)
		return -1;
	return 0;
}
