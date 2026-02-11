filename_filter(const char * file) {
	if (!file) { return 0; }
	if (strlen(file) < 5) { return 0; }
	const char * ext = file + strlen(file)-4;
	if (strcmp(ext, ".wav") == 0) {	return 1; }
	if (strcmp(ext, ".WAV") == 0) {	return 1; }
	if (strcmp(ext, ".aiff") == 0) { return 1; }
	if (strcmp(ext, ".AIFF") == 0) { return 1; }
	if (strcmp(ext, ".au") == 0) { return 1; }
	if (strcmp(ext, ".AU") == 0) { return 1; }
	if (strcmp(ext, ".flac") == 0) { return 1; }
	if (strcmp(ext, ".FLAC") == 0) { return 1; }
	if (strcmp(ext, ".ogg") == 0) { return 1; }
	if (strcmp(ext, ".OGG") == 0) { return 1; }
	return 0;
}
