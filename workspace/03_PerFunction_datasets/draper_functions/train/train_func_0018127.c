calcsum(unsigned char *fwbuf)
{
	unsigned int flashsum, i;

	for(flashsum = 0, i = 0; i < FLASHSIZE; i++)
		flashsum += fwbuf[i];

	return (flashsum & 0xffff);
}
