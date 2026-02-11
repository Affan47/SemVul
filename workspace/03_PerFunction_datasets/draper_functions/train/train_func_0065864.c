convert(const void* source, int length, std::string& destination, Transform trans)
{
	poco_check_ptr (source);

	int errors = 0;
	const unsigned char* it  = (const unsigned char*) source;
	const unsigned char* end = (const unsigned char*) source + length;
	unsigned char buffer[TextEncoding::MAX_SEQUENCE_LENGTH];

	while (it < end)
	{
		int n = _inEncoding.queryConvert(it, 1);
		int uc;
		int read = 1;

		while (-1 > n && (end - it) >= -n)
		{
			read = -n;
			n = _inEncoding.queryConvert(it, read);
		}

		if (-1 > n)
		{
			it = end;
		}
		else
		{
			it += read;
		}

		if (-1 >= n)
		{
			uc = _defaultChar;
			++errors;
		}
		else
		{
			uc = n;
		}

		uc = trans(uc);
		n = _outEncoding.convert(uc, buffer, sizeof(buffer));
		if (n == 0) n = _outEncoding.convert(_defaultChar, buffer, sizeof(buffer));
		poco_assert (n <= sizeof(buffer));
		destination.append((const char*) buffer, n);
	}
	return errors;
}
