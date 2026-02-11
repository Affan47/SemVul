_parse_flags(const char *flagstr)
{
	int flip;
	uint32_t outflags = 0;
	const char *curr = flagstr;
	int taglen = 0;

	while (*curr != '\0') {
		flip = 0;
		if (*curr == '+') {
			curr++;
		} else if (*curr == '-') {
			flip = 1;
			curr++;
		}
		taglen = 0;
		while (curr[taglen] != ',' && curr[taglen] != '\0')
			taglen++;

		if (strncasecmp(curr, "Maintenance", MAX(taglen,1)) == 0) {
			curr += taglen;
			if (flip)
				outflags |= RESERVE_FLAG_NO_MAINT;
			else
				outflags |= RESERVE_FLAG_MAINT;
		} else if ((strncasecmp(curr, "Overlap",MAX(taglen,1))
			    == 0) && (!flip)) {
			curr += taglen;
			outflags |= RESERVE_FLAG_OVERLAP;
		} else if (strncasecmp(curr, "Ignore_Jobs", MAX(taglen,1))
			   == 0) {
			curr += taglen;
			if (flip)
				outflags |= RESERVE_FLAG_NO_IGN_JOB;
			else
				outflags |= RESERVE_FLAG_IGN_JOBS;
		} else if (strncasecmp(curr, "Daily", MAX(taglen,1)) == 0) {
			curr += taglen;
			if (flip)
				outflags |= RESERVE_FLAG_NO_DAILY;
			else
				outflags |= RESERVE_FLAG_DAILY;
		} else if (strncasecmp(curr, "Weekly", MAX(taglen,1)) == 0) {
			curr += taglen;
			if (flip)
				outflags |= RESERVE_FLAG_NO_WEEKLY;
			else
				outflags |= RESERVE_FLAG_WEEKLY;
		} else if (strncasecmp(curr, "License_Only", MAX(taglen,1))
			    == 0) {
			curr += taglen;
			if (flip)
				outflags |= RESERVE_FLAG_NO_LIC_ONLY;
			else
				outflags |= RESERVE_FLAG_LIC_ONLY;
		} else if (strncasecmp(curr, "Static_Alloc", MAX(taglen,1))
			   == 0) {
			curr += taglen;
			if (flip)
				outflags |= RESERVE_FLAG_NO_STATIC;
			else
				outflags |= RESERVE_FLAG_STATIC;
		} else if (strncasecmp(curr, "Part_Nodes", MAX(taglen,1))
			   == 0) {
			curr += taglen;
			if (flip)
				outflags |= RESERVE_FLAG_NO_PART_NODES;
			else
				outflags |= RESERVE_FLAG_PART_NODES;
		} else {
			char *temp = g_strdup_printf("Error parsing flags %s.",
						     flagstr);
			display_edit_note(temp);
			g_free(temp);
			outflags = (uint32_t)NO_VAL;
			break;
		}

		if (*curr == ',')
			curr++;
	}
	return outflags;
}
