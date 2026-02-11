rol(unsigned char* out, const unsigned char* in, unsigned int s)
{
	unsigned char firstbit = in[0] >> 7;
	while (--s > 0) {
		unsigned char bit = in[1] >> 7;

		*out++ = (*in++ << 1) | bit;
	}

	*out = (*in << 1) | firstbit;
}
