parse_scroll_copyrect(void) {
	parse_scroll_copyrect_str(SCROLL_COPYRECT_PARMS);
	if (! scroll_copyrect_str) {
		scroll_copyrect_str = strdup(SCROLL_COPYRECT_PARMS);
	}
	parse_scroll_copyrect_str(scroll_copyrect_str);
}
