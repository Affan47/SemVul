Get5bits(const unsigned char *in, int i)
{
	unsigned int x = in[(5*i)/8] << 8;
	if ((5*i)%8 > (8-5)) x |= in[((5*i)/8)+1];

	x <<= (5*i)%8;
	return (x&0xFFFF) >> (16-5);
}
