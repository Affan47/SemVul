parse_unbinding(char *ptr)
{
    char *keyptr = NULL, *keycopy = NULL, *menuptr = NULL;
    sc *s;
    int i, menu;

    assert(ptr != NULL);

    if (*ptr == '\0') {
	rcfile_error(N_("Missing key name"));
	return;
    }

    keyptr = ptr;
    ptr = parse_next_word(ptr);
    keycopy = mallocstrcpy(NULL, keyptr);
    for (i = 0; i < strlen(keycopy); i++)
	keycopy[i] = toupper(keycopy[i]);

#ifdef DEBUG
    fprintf(stderr, "Starting unbinding code");
#endif

    if (keycopy[0] != 'M' && keycopy[0] != '^' && keycopy[0] != 'F' && keycopy[0] != 'K') {
	rcfile_error(
		N_("keybindings must begin with \"^\", \"M\", or \"F\""));
	return;
    }

    menuptr = ptr;
    ptr = parse_next_word(ptr);

    if (!strcmp(menuptr, "")) {
	rcfile_error(


		N_("Must specify menu to bind key to (or \"all\")"));
	return;
    }

    menu = strtomenu(menuptr);
    if (menu < 1) {
	rcfile_error(
		N_("Could not map name \"%s\" to a menu"), menuptr);
	return;
    }


#ifdef DEBUG
    fprintf(stderr, "unbinding \"%s\" from menu = %d\n", keycopy, menu);
#endif


    for (s = sclist; s != NULL; s = s->next) {
        if (((s->menu & menu)) && !strcmp(s->keystr,keycopy)) {
	    s->menu &= ~menu;
#ifdef DEBUG
	    fprintf(stderr, "deleted menu entry %d\n", s->menu);
#endif
	}
    }
}
