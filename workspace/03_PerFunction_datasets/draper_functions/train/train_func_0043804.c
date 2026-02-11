dump_skipped_provider(char *str, int len) {
	int colour = BLACK;
	struct skip *entry = list[colour];
	char *end = str + len, *p;
	int n = 0, v;
	char range[64];

	if (len < 1)
		return -1;
	*str = '\0';

	if (!entry && colour == BLACK)
		entry = list[colour = WHITE];
	while (entry && str < end) {


		p = range;
		*p = '\0';
		if (entry->flags & FLAG_PROV0) {
			p += snprintf(p, 15, "%i", entry->prov[0]);
			if (entry->flags & FLAG_VAR0)
				p += snprintf(p, 15, ",%i", entry->var[0]);
		}


		if ((entry->flags & (FLAG_PROV0|FLAG_PROV1)) != (FLAG_PROV0|FLAG_PROV1) ||
		    entry->prov[0] != entry->prov[1] ||
		    ( (v=(entry->flags & (FLAG_VAR0|FLAG_VAR1))) == (FLAG_VAR0|FLAG_VAR1)
        && entry->var[0] != entry->var[1] ) ||
		    v == FLAG_VAR0 || v== FLAG_VAR1) {
			*p++ = '-';
			if (entry->flags & FLAG_PROV1) {
				p += snprintf(p, 15, "%i", entry->prov[1]);
				if (entry->flags & FLAG_VAR1)
					p += snprintf(p, 15, ",%i", entry->var[1]);
			}
		}
		if (entry->flags & FLAG_ALL) {

			range[0] = '*';
			range[1] = '\0';
		}

		str += snprintf(str, end-str, "%s%s%s%s", n ? ";" : "", range,
		                entry->flags & FLAG_WHITE  ? "~" : "",
		                entry->flags & FLAG_UNCOND ? "!" : "");

		++n;
		entry = entry->next;
		if (!entry && colour == BLACK)
			entry = list[colour = WHITE];
	}

	return (entry) ? -1 : n;
}
