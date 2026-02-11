parseLine(std::istream& istr)
{
	static const int eof = std::char_traits<char>::eof();

	int c = istr.get();
	while (c != eof && Poco::Ascii::isSpace(c)) c = istr.get();
	if (c != eof)
	{
		if (c == '#' || c == '!')
		{
			while (c != eof && c != '\n' && c != '\r') c = istr.get();
		}
		else
		{
			std::string key;
			while (c != eof && c != '=' && c != ':' && c != '\r' && c != '\n') { key += (char) c; c = istr.get(); }
			std::string value;
			if (c == '=' || c == ':')
			{
				c = readChar(istr);
				while (c != eof && c) { value += (char) c; c = readChar(istr); }
			}
			setRaw(trim(key), trim(value));
		}
	}
}
