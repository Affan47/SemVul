current_line_indentation(struct view *view, position_t *at)
{
	int indent = 0, spaces = 0, chars = 0;
	position_t offset = *at;
	Unicode_t ch;
	unsigned tabstop = view->text->tabstop;

	while (IS_UNICODE(ch = view_char(view, offset, &offset)) && ch != '\n')
		if (ch == ' ')
			spaces += !chars;
		else if (ch == '\t') {
			indent = ((indent + spaces + chars) /
				  tabstop + 1) * tabstop;
			spaces = chars = 0;
			*at = offset;
		} else
			chars++;
	*at += spaces;
	return indent + spaces;
}
