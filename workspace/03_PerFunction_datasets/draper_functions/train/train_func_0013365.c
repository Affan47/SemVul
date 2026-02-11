set_page_sizeCmd()
{
	Require(_nword == 4, err("`set page size' requires 1 parameter"));
	const char *s = _word[3];
	extern rectangle _page_size;
	if (!strcmp(s, "letter")) {
		_page_size.set(0.0, 0.0, 8.5, 11.0);
		_page_size.scale(CM_PER_IN);
	} else if (!strcmp(s, "legal")) {
		_page_size.set(0.0, 0.0, 8.5, 14.0);
		_page_size.scale(CM_PER_IN);
	} else if (!strcmp(s, "folio")) {
		_page_size.set(0.0, 0.0, 8.5, 13.0);
		_page_size.scale(CM_PER_IN);
	} else if (!strcmp(s, "tabloid")) {
		_page_size.set(0.0, 0.0, 11.0, 17.0);
		_page_size.scale(CM_PER_IN);
	} else if (!strcmp(s, "A5")) {
		_page_size.set(0.0, 0.0, 14.8, 21.0);
	} else if (!strcmp(s, "A4")) {
		_page_size.set(0.0, 0.0, 21.0, 29.7);
	} else if (!strcmp(s, "A3")) {
		_page_size.set(0.0, 0.0, 29.7, 42.0);
	} else if (!strcmp(s, "A2")) {
		_page_size.set(0.0, 0.0, 42.0, 59.4);
	} else if (!strcmp(s, "A1")) {
		_page_size.set(0.0, 0.0, 59.4, 84.1);
	} else if (!strcmp(s, "A0")) {
		_page_size.set(0.0, 0.0, 84.1, 118.9);
	} else {
		demonstrate_command_usage();
		err("Unknown paper size `\\", s, "'.", "\\");
		return false;
	}
	return true;
}
