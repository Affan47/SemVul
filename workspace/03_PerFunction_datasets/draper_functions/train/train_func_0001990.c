read(istream & is)
{
	Lexer lexrc(lyxrcTags);
	lexrc.setStream(is);
	LYXERR(Debug::LYXRC, "Reading istream...");
	return read(lexrc, false) == ReadOK;
}
