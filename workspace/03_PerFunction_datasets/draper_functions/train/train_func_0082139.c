series_is_log (const DATASET *dset, int i, char *parent)
{
    const char *s = series_get_label(dset, i);

    *parent = '\0';

    if (s != NULL && *s != '\0') {
	char fmt[16];

	sprintf(fmt, "= log of %%%ds", VNAMELEN-1);

	if (sscanf(s, fmt, parent) == 1) {
	    return 1;
	} else if (!strncmp(s, "log(", 4)) {
	    return found_log_parent(s + 4, parent);
	} else {
	    s += strcspn(s, "=");
	    if (!strncmp(s, "=log(", 5)) {
		return found_log_parent(s + 5, parent);
	    }
	}
    }

    return 0;
}
