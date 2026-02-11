mod_status_get_multiplier(double *avg, char *multiplier, int size) {
	*multiplier = ' ';

	if (*avg > size) { *avg /= size; *multiplier = 'k'; }
	if (*avg > size) { *avg /= size; *multiplier = 'M'; }
	if (*avg > size) { *avg /= size; *multiplier = 'G'; }
	if (*avg > size) { *avg /= size; *multiplier = 'T'; }
	if (*avg > size) { *avg /= size; *multiplier = 'P'; }
	if (*avg > size) { *avg /= size; *multiplier = 'E'; }
	if (*avg > size) { *avg /= size; *multiplier = 'Z'; }
	if (*avg > size) { *avg /= size; *multiplier = 'Y'; }

	return 0;
}
