get_ssst(char s)
{
	if (strchr(".,:;+-*/=()[]", s)) {
		return ssst_separator;
	} else if (s==' ') {
		return ssst_whitespace;
	}
	return ssst_word;
}
