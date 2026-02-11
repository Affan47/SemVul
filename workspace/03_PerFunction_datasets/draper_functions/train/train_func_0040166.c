quote (const char* str)	{
	std::string outstr ( str );
	outstr.insert (0, 1, '\'');
	outstr += '\'';
	return outstr;
}
