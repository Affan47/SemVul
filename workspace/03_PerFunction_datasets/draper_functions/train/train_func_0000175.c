write_internal_format(FILE *out) {
	pos_format   = PSEDIT_POS_FORMAT;
	size_format  = PSEDIT_SIZE_FORMAT;
	color_format = PSEDIT_COLOR_FORMAT;
	text_format  = PSEDIT_TEXT_FORMAT_PRINT;
	glyph_format = PSEDIT_GLYPH_FORMAT;
	tag_format   = PSEDIT_TAG_FORMAT;

	for (int i = 1; i < pse->get_max_pages(); i++) {
		if (pse->get_text(i)) {
			fprintf(out, PSEDIT_PAGE_FORMAT, i);
			write_text(out, pse->get_text(i));
		}
	}
}
