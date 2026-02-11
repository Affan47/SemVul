unshuffleBytes(unsigned char *buf, int size)
{
    for(int i=size-1; i; --i)
	buf[i] ^= buf[i-1];
}
