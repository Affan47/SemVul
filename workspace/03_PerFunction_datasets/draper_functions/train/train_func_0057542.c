readFromDevice(char* buffer, std::streamsize length)
{

	static const int eof = std::char_traits<char>::eof();

	if (_end) return 0;

	int n = 0;
	int ch = _session.get();
	while (ch != eof && ch != '\n' && n < length - 1)
	{
		*buffer++ = (char) ch; ++n;
		ch = _session.get();
	}
	if (ch != eof)
	{
		*buffer++ = (char) ch; ++n;
		if (n == 2) _end = true;
	}
	return n;
}
