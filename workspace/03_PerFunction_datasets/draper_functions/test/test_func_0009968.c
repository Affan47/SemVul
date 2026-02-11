initialize_scroll_term(void) {
	char *str;
	int n;

	destroy_str_list(scroll_term);
	scroll_term = NULL;

	if (scroll_term_str != NULL && *scroll_term_str != '\0') {
		str = scroll_term_str;
	} else {
		str = scroll_term_str0;
	}
	if (!strcmp(str, "none")) {
		return;
	}
	scroll_term = create_str_list(str);

	n = 0;
	while (scroll_term[n] != NULL) {
		char *s = scroll_good_all[n++];

		s = NULL;
	}
}
