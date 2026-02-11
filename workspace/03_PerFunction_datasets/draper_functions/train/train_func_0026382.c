read_number_bad_syntax_msg (const char * string, const char * string_limit)
{
	std::ostringstream buf;
	fprint(buf, "Illegal number syntax: \"");
	for (const char * ptr = string; ptr != string_limit; ptr++)
		fprintchar(buf, *ptr);
	fprint(buf, "\"");
	return buf.str();
}
