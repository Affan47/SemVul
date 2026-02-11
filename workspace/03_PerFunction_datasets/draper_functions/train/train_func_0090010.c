shell_quote(const String &str)
{
#if defined(_MSDOS) || defined(_WIN32)
    return str;
#else
    if (!str)
	return String::make_stable("''");

    const char *begin = str.begin();
    const char *end = str.end();
    StringAccum sa;
    for (const char *s = begin; s < end; s++)
	if (isalnum((unsigned char) *s) || *s == '_' || *s == '-' || *s == '+' || *s == '/' || *s == ':' || *s == '.')
	    ;
	else {
	    sa.append(begin, s);
	    sa.append('\\');
	    begin = s;
	}

    if (!sa)
	return str;
    else {
	sa.append(begin, end);
	return sa.take_string();
    }
#endif
}
