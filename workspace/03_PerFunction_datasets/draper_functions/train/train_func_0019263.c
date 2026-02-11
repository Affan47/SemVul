wchar_to_utf8(char* output, wchar_t wc, size_t outsize)
{
	if (wc <= 0x7f)
	{
		if (outsize < 1)
			return NULL;
		*output++ = (char) wc;
	}
	else if (wc <= 0x7ff)
	{
		if (outsize < 2)
			return NULL;
		*output++ = 0xc0 | (wc >> 6);
		*output++ = 0x80 | (wc & 0x3f);
	}
	else if (wc <= 0xffff)
	{
		if (outsize < 3)
			return NULL;
		*output++ = 0xe0 | (wc >> 12);
		*output++ = 0x80 | ((wc >> 6) & 0x3f);
		*output++ = 0x80 | (wc & 0x3f);
	}
	else if (wc <= 0x1fffff)
	{
		if (outsize < 4)
			return NULL;
		*output++ = 0xf0 | (wc >> 18);
		*output++ = 0x80 | ((wc >> 12) & 0x3f);
		*output++ = 0x80 | ((wc >> 6) & 0x3f);
		*output++ = 0x80 | (wc & 0x3f);
	}
	else if (wc <= 0x3ffffff)
	{
		if (outsize < 5)
			return NULL;
		*output++ = 0xf8 | (wc >> 24);
		*output++ = 0x80 | ((wc >> 18) & 0x3f);
		*output++ = 0x80 | ((wc >> 12) & 0x3f);
		*output++ = 0x80 | ((wc >> 6) & 0x3f);
		*output++ = 0x80 | (wc & 0x3f);
	}
	else if (wc <= 0x7fffffff)
	{
		if (outsize < 6)
			return NULL;
		*output++ = 0xfc | (wc >> 30);
		*output++ = 0x80 | ((wc >> 24) & 0x3f);
		*output++ = 0x80 | ((wc >> 18) & 0x3f);
		*output++ = 0x80 | ((wc >> 12) & 0x3f);
		*output++ = 0x80 | ((wc >> 6) & 0x3f);
		*output++ = 0x80 | (wc & 0x3f);
	}
	else
		return NULL;

	return output;
}
