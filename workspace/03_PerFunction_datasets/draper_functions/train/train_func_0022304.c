convert(const unsigned char* bytes) const
{
	int n = _charMap[*bytes];
	int uc;

	switch (n)
	{
	case -6:
	case -5:
	case -1:
		return -1;
	case -4:
	case -3:
	case -2:
		if (!isLegal(bytes, -n)) return -1;
		uc = *bytes & ((0x07 << (n + 4)) | 0x03);
		break;
	default:
		return n;
	}

	while (n++ < -1)
	{
		uc <<= 6;
		uc |= (*++bytes & 0x3F);
	}
	return uc;
}
