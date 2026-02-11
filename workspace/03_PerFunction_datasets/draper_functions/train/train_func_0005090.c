mkauthor(const char *text, int cols, enum author author)
{
	bool trim = author_trim(cols);
	bool abbreviate = author == AUTHOR_ABBREVIATED || !trim;

	if (author == AUTHOR_NO)
		return "";
	if (abbreviate && text)
		return get_author_initials(text);
	return text;
}
