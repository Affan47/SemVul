parse_null(const char** pcursor, float* dest) {
	int nchars;
	if (!strncmp(*pcursor, "\\N|", 3)) {
		*dest = TWOMASS_NULL;
		*pcursor += 3;
		return 0;
	}
	if (sscanf(*pcursor, "%f|%n", dest, &nchars) != 1) {
		return -1;
	}
	*pcursor += nchars;
	return 0;
}
