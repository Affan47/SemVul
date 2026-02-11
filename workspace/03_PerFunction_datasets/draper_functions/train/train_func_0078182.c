check_colspec (const char *s)
{
    const char *ok = "eEfgG";
    int w = 0, p = 0;
    char c = 0;
    int err = 1;


    if (*s == '\0') {
	return 0;
    }

    if (*s != '%') {
	return 1;
    }

    s++;

    if (*s == '#') {
	s++;
    }

    if (sscanf(s, "%d.%d%c", &w, &p, &c) == 3) {
	if (w != 0 && p > 0 && strchr(ok, c)) {
	    err = 0;
	}
    } else if (sscanf(s, "%d%c", &w, &c) == 2) {
	if (w != 0 && strchr(ok, c)) {
	    err = 0;
	}
    } else if (sscanf(s, ".%d%c", &p, &c) == 2) {
	if (p > 0 && strchr(ok, c)) {
	    err = 0;
	}
    } else if (sscanf(s, "%c", &c) == 1) {
	if (strchr(ok, c)) {
	    err = 0;
	}
    }

    return err;
}
