clearblock(unsigned int N)
{
	unsigned char buffer[24];

	if (fd < 0) return -1;
	memset(buffer,0,24);
	return writeblock(N,buffer);
}
