Utf8LengthFromUtf16(const char* data, size_t tlen, FileEncoding encoding) const
{
	enum { SURROGATE_LEAD_FIRST = 0xD800 };
	enum { SURROGATE_TRAIL_LAST = 0xDFFF };

	size_t len = 0;
	size_t wcharLen = tlen / 2;
	const short* uptr = reinterpret_cast<const short*>(data);
	for (size_t i = 0; i < wcharLen && uptr[i];)
	{
		size_t uch = encoding == UTF_16BE ? swap16bit(uptr[i]) : uptr[i];
		if (uch < 0x80)
		{
			len++;
		}
		else if (uch < 0x800)
		{
			len += 2;
		}
		else if ((uch >= SURROGATE_LEAD_FIRST) && (uch <= SURROGATE_TRAIL_LAST))
		{
			len += 4;
			i++;
		}
		else
		{
			len += 3;
		}
		i++;
	}
	return len;
}
