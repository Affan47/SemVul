popup_split_lines(popup_info *pi, int flags)
{
	int	nlines, i, body_offset = 0;
	int	n_chars[POPUP_MAX_LINES];
	char	*p_str[POPUP_MAX_LINES];

	gr_set_font(FONT1);
	n_chars[0]=0;

	nlines = split_str(pi->raw_text, 1000, n_chars, p_str, POPUP_MAX_LINES);
	Assert(nlines >= 0 && nlines <= POPUP_MAX_LINES );

	if ( flags & (PF_TITLE | PF_TITLE_BIG) ) {

		strncpy(pi->title, p_str[0], n_chars[0]);
		pi->title[n_chars[0]] = 0;
		body_offset = 1;
	}

	if ( flags & PF_BODY_BIG ) {
		gr_set_font(FONT2);
	}

	nlines = split_str(pi->raw_text, Popup_text_coords[gr_screen.res][2], n_chars, p_str, POPUP_MAX_LINES);
	Assert(nlines >= 0 && nlines <= POPUP_MAX_LINES );

	pi->nlines = nlines - body_offset;

	for ( i = 0; i < pi->nlines; i++ ) {
		Assert(n_chars[i+body_offset] < POPUP_MAX_LINE_CHARS);
		strncpy(pi->msg_lines[i], p_str[i+body_offset], n_chars[i+body_offset]);
		pi->msg_lines[i][n_chars[i+body_offset]] = 0;
	}

	gr_set_font(FONT1);
}
