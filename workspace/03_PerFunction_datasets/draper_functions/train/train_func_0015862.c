Put2(const byte *inString, size_t length, int messageEnd, bool blocking)
{
	while (length--)
	{
		byte inByte = *inString++;
		if (n >= Q)
			sum += log(double(n - tab[inByte]));
		tab[inByte] = n;
		n++;
	}
	return 0;
}
