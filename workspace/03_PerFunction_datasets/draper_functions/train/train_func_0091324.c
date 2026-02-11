ae_strtofflags(const char *s, unsigned long *setp, unsigned long *clrp)
{
	const char *start, *end;
	struct flag *flag;
	unsigned long set, clear;
	const char *failed;

	set = clear = 0;
	start = s;
	failed = NULL;

	while (*start == '\t'  ||  *start == ' '  ||  *start == ',')
		start++;
	while (*start != '\0') {

		end = start;
		while (*end != '\0'  &&  *end != '\t'  &&
		    *end != ' '  &&  *end != ',')
			end++;
		for (flag = flags; flag->name != NULL; flag++) {
			if (memcmp(start, flag->name, end - start) == 0) {

				clear |= flag->set;
				set |= flag->clear;
				break;
			} else if (memcmp(start, flag->name + 2, end - start)
			    == 0) {

				set |= flag->set;
				clear |= flag->clear;
				break;
			}
		}

		if (flag->name == NULL  &&  failed == NULL)
			failed = start;


		start = end;
		while (*start == '\t'  ||  *start == ' '  ||  *start == ',')
			start++;

	}

	if (setp)
		*setp = set;
	if (clrp)
		*clrp = clear;


	return (failed);
}
