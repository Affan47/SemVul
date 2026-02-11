scan_ID3_optargs(char *argv[], int start_optargs, char* &target_lang, uint16_t &packed_lang, uint8_t &char_encoding, char* meta_container, bool &multistring) {
	packed_lang = 5575;
	uint16_t i = 0;

	while (argv[start_optargs + i] != NULL) {
		if ( argv[start_optargs + i] && start_optargs + i <= total_args ) {

			if ( memcmp(argv[start_optargs + i], "lang=", 5) == 0 ) {
				if (!MatchLanguageCode(argv[start_optargs +i]+5) ) {
					packed_lang = PackLanguage("und", 0);
					target_lang = "und";
				} else {
					packed_lang = PackLanguage(argv[start_optargs +i], 5);
					target_lang = argv[start_optargs + i] + 5;
				}

			} else if ( memcmp(argv[start_optargs + i], "UTF16LE", 8) == 0 ) {
				char_encoding = TE_UTF16LE_WITH_BOM;
			} else if ( memcmp(argv[start_optargs + i], "UTF16BE", 8) == 0 ) {
				char_encoding = TE_UTF16BE_NO_BOM;
			} else if ( memcmp(argv[start_optargs + i], "LATIN1", 7) == 0 ) {
				char_encoding = TE_LATIN1;

			} else if ( memcmp(argv[optind + i], "root", 5) == 0 ) {
				*meta_container = 0-FILE_LEVEL_ATOM;
			} else if ( memcmp(argv[optind + i], "track=", 6) == 0 ) {
				char* track_index_str = argv[optind + i];
				strsep(&track_index_str, "=");
				sscanf(track_index_str, "%hhu", meta_container);
			}
		}

		if (memcmp(argv[start_optargs + i], "-", 1) == 0) {
			break;
		}
		i++;
	}
	return;
}
