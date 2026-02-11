next_processing_code(const String &str, int &pos, ErrorHandler *errh,
		     const String &landmark, ElementClassT *etype)
{
    const char *s = str.data();
    int len = str.length();
    if (pos >= len)
	return -2;

    switch (s[pos]) {

      case 'h': case 'H':
	pos++;
	return ProcessingT::VPUSH;

      case 'l': case 'L':
	pos++;
	return ProcessingT::VPULL;

      case 'a': case 'A':
	pos++;
	return ProcessingT::VAGNOSTIC;

      case '/':
	return -2;

      default:
	errh->lerror(landmark, "bad character '%c' in processing code for '%s'", s[pos], etype->printable_name_c_str());
	pos++;
	return -1;

    }
}
