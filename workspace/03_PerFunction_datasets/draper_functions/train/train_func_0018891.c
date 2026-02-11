C_comment_end(struct view *view, position_t offset)
{
	Unicode_t ch, lch = 0;
	position_t next;

	if (view_char(view, offset, &offset) != '/')
		return -1;
	ch = view_char(view, offset, &offset);
	if (ch == '/')
		return find_line_end(view, offset);
	if (ch != '*')
		return -1;
	while (IS_UNICODE((ch = view_char(view, offset, &next)))) {
		if (lch == '*' && ch == '/')
			return offset;
		lch = ch;
		offset = next;
	}
	return -1;
}
