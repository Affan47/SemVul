_synctex_scan_postamble(synctex_scanner_t scanner) {
	int status = 0;
	if (NULL == scanner) {
		return SYNCTEX_STATUS_BAD_ARGUMENT;
	}
	status = _synctex_match_string(scanner,"Postamble:");
	if (status < SYNCTEX_STATUS_OK) {
		return status;
	}
count_again:
	status = _synctex_next_line(scanner);
	if (status < SYNCTEX_STATUS_OK) {
		return status;
	}
	status = _synctex_scan_named(scanner,"Count:",&(scanner->count),(synctex_decoder_t)&_synctex_decode_int);
	if (status < SYNCTEX_STATUS_EOF) {
		return status;
	} else if (status < SYNCTEX_STATUS_OK) {
		status = _synctex_next_line(scanner);
		if (status<SYNCTEX_STATUS_OK) {
			return status;
		}
		goto count_again;
	}

	return _synctex_scan_post_scriptum(scanner);
}
