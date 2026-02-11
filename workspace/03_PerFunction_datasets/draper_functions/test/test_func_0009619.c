find_paragraph_start(struct view *view, position_t offset)
{
	Unicode_t ch, nch = UNICODE_BAD, nnch = UNICODE_BAD;
	position_t prev;

	while (IS_UNICODE((ch = view_char_prior(view, offset, &prev)))) {
		if (ch == '\n' && nch == '\n' && IS_UNICODE(nnch))
			return offset + 1;
		offset = prev, nnch = nch, nch = ch;
	}
	return offset;
}
