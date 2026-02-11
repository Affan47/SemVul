cmd_ADDSOURCE(int in_clid, KisNetFramework *framework,
									   char *errstr, string cmdline,
									   vector<smart_word_token> *parsedcmdline) {
	if (parsedcmdline->size() < 1) {
		snprintf(errstr, 1024, "Illegal ADDSOURCE command, expected source line");
		return -1;
	}

	uint16_t new_source_id;

	int ret = AddPacketSource((*parsedcmdline)[0].word, NULL, &new_source_id);

	if (ret <= 0) {
		snprintf(errstr, 1024, "ADDSOURCE command failed");
		return -1;
	}

	_MSG("Added source '" + (*parsedcmdline)[0].word + "' from client ADDSOURCE",
		 MSGFLAG_INFO);

	if (StartSource(new_source_id) < 0) {
		snprintf(errstr, 1024, "ADDSOURCE failed to activate new source");
		return -1;
	}

	snprintf(errstr, 1024, "Created new source");

	return 1;
}
