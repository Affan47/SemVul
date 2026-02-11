set_shelldir (const char *s)
{
    int len = 0, err = 0;


    s += 12;
    s += strspn(s, " ");

    if (*s == '\0') {
	*state->shelldir = '\0';
	gretl_insert_builtin_string("shelldir", state->shelldir);
    } else if (*s == '"') {
	s++;
	len = gretl_charpos('"', s);
	if (len <= 0) {
	    err = E_PARSE;
	}
    } else {
	len = strlen(s);
    }

    if (!err && len > 0) {
	char test[MAXLEN];
	char *home = NULL;
	int slen = len;

	if (*s == '~') {
	    home = getenv("HOME");
	    if (home != NULL) {
		s++;
		slen--;
		len = slen + strlen(home);
	    }
	}

	*test = '\0';

	if (len >= MAXLEN) {
	    gretl_errmsg_set("shelldir: string is too long");
	    err = E_DATA;
	} else if (home != NULL) {
	    strcat(test, home);
	    strncat(test, s, slen);
	} else {
	    strncat(test, s, len);
	}

	if (!gretl_isdir(test)) {
	    gretl_errmsg_sprintf("shelldir: '%s' no such directory", test);
	    err = E_DATA;
	}

	if (!err) {
	    strcpy(state->shelldir, test);
	    gretl_insert_builtin_string("shelldir", state->shelldir);
	}
    }

    return err;
}
