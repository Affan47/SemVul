write_label(std::ostringstream &buffer, const char *label)
{
	std::string buf;
	pattern_t ptype;

	if (label) {
		int pos;
		ptype = convert_aaregex_to_pcre(label, 0, glob_default, buf, &pos);
		if (ptype == ePatternInvalid)
			return false;

		buffer << buf;
	} else
		buffer << default_match_pattern;

	return true;
}
