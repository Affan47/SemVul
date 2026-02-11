add_indent(const String &indent, int spaces)
{
    String new_indent;
    const char *s = indent.data();
    int last_col = 0, col = 0, len = indent.length();
    for (int pos = 0; pos < len; pos++)
	if (s[pos] == '\t')
	    col = (col + 8) & ~7;
	else if (s[pos] == ' ')
	    col++;
	else {
	    space_until(new_indent, last_col, col);
	    new_indent += s[pos];
	    col++;
	    last_col = col;
	}
    space_until(new_indent, last_col, col + spaces);
    return new_indent;
}
