is_dd_mon_yyyy(char *t)
{
	char *instr;
	char month[4];

	instr = t;

	if (!isdigit((unsigned char) *instr))
		return (0);

	instr++;

	if (!isdigit((unsigned char) *instr))
		return (0);

	instr++;

	if (*instr == '-') {
		instr++;

		strncpy(month, instr, 3);
		month[3] = '\0';

		if (!is_monthname(month))
			return (0);

		instr += 3;

		if (*instr != '-')
			return (0);

		instr++;
		if (!isdigit((unsigned char) *instr))
			return (0);

		instr++;
		if (!isdigit((unsigned char) *instr))
			return (0);

		instr++;

		if (*instr) {
			if (!isdigit((unsigned char) *instr))
				return (0);

			instr++;
			if (!isdigit((unsigned char) *instr))
				return (0);
		}

	} else {

		strncpy(month, instr, 3);
		month[3] = '\0';

		if (!is_monthname(month))
			return (0);

		instr += 3;

		if (!isdigit((unsigned char) *instr))
			return (0);

		instr++;
		if (!isdigit((unsigned char) *instr))
			return (0);

		instr++;
		if (*instr) {
			if (!isdigit((unsigned char) *instr))
				return (0);

			instr++;
			if (!isdigit((unsigned char) *instr))
				return (0);
		}
	}

	return (1);

}
