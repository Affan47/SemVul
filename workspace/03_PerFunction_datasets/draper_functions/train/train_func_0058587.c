find_signal_mapping(const char *sig)
{
	if (strncmp("rtmin+", sig, 6) == 0) {
		char *end;
		unsigned long n = strtoul(sig + 6, &end, 10);
		if (end == sig || n > MAXRT_SIG)
			return -1;
		return MINRT_SIG + n;
	} else {
		for (int i = 0; signal_map[i].name; i++) {
			if (strcmp(sig, signal_map[i].name) == 0)
				return signal_map[i].num;
		}
	}
	return -1;
}
