toUTF16(const std::string& utf8String, std::wstring& utf16String)
{
	utf16String.clear();
	UTF8Encoding utf8Encoding;
	TextIterator it(utf8String, utf8Encoding);
	TextIterator end(utf8String);
	while (it != end)
	{
		int cc = *it++;
		if (cc <= 0xffff)
		{
			utf16String += (wchar_t) cc;
		}
		else
		{
			cc -= 0x10000;
			utf16String += (wchar_t) ((cc >> 10) & 0x3ff) | 0xd800;
			utf16String += (wchar_t) (cc & 0x3ff) | 0xdc00;
		}
	}
}
