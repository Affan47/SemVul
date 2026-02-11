read7BitEncoded(UInt32& value)
{
	char c;
	value = 0;
	int s = 0;
	do
	{
		c = 0;
		_istr.read(&c, 1);
		UInt32 x = (c & 0x7F);
		x <<= s;
		value += x;
		s += 7;
	}
	while (c & 0x80);
}
