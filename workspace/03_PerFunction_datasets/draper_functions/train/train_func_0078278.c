saveMessageContents(std::string s)
{
	byteCount += s.size();

	if (tfile)
		if (fwrite(s.c_str(), s.size(), 1, tfile) != 1)
			;
}
