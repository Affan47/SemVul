cmd_hash()
{
	CMD_REQUIRE_ARGS(1);
	const std::string param = cmd_args[1];

	if (param == "clear") {
		if (hashtable) {
			search->stop_thread();
			hashtable->clear();
			printf("Hash table cleared.\n");
		} else {
			printf("Error: hash table is disabled\n");
		}
	} else if (param == "size") {
	 	CMD_REQUIRE_ARGS(2);
		const char * s = cmd_args[2].c_str();
		long size;
		if (!parse_size(s, &size) || size < 0) {
			printf("Illegal value for hash table size: %s\n",
					s);
			return;
		}
		search->stop_thread();
		set_hashsize((unsigned) size);
	} else if (param == "off") {
		search->stop_thread();
		set_hashsize(0);
	} else if (param == "info") {
		if (hashtable) {
			hashtable->print_info();
		} else {
			printf("Hash table is disabled.\n");
		}
	} else if (param == "stats") {
		if (hashtable) {
			hashtable->print_statistics();
		} else {
			printf("Error: hash table is disabled\n");
		}
	} else if (param == "replace") {
		CMD_REQUIRE_ARGS(2);
		if (hashtable) {
			hashtable->set_replacement_scheme(cmd_args[2]);
		} else {
			printf("Error: hash table is disabled\n");
		}
	} else {
		printf("Usage: hash clear\n");
		printf("       hash size <size>\n");
		printf("       hash off\n");
		printf("       hash info\n");
		printf("       hash stats\n");
	}
}
