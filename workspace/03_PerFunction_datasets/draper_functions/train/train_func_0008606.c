slurmdb_parse_purge(char *string)
{
	int i = 0;
	uint32_t purge = NO_VAL;

	xassert(string);

	while(string[i]) {
		if ((string[i] >= '0') && (string[i] <= '9')) {
			if(purge == NO_VAL)
				purge = 0;
                        purge = (purge * 10) + (string[i] - '0');
                } else
			break;
		i++;
	}

	if (purge != NO_VAL) {
		int len = strlen(string+i);
		if(!len || !strncasecmp("months", string+i, MAX(len, 1))) {
			purge |= SLURMDB_PURGE_MONTHS;
		} else if(!strncasecmp("hours", string+i, MAX(len, 1))) {
			purge |= SLURMDB_PURGE_HOURS;
		} else if(!strncasecmp("days", string+i, MAX(len, 1))) {
			purge |= SLURMDB_PURGE_DAYS;
		} else {
			error("Invalid purge unit '%s', valid options "
			      "are hours, days, or months", string+i);
			purge = NO_VAL;
		}
	} else
		error("Invalid purge string '%s'", string);

	return purge;
}
