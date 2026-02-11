db_match_prep(const char *prepname)
{
    db_prep_spec prep;
    int argc;
    char *ptr;
    char **argv;
    char *s, first;

    s = str_dup(prepname);
    first = s[0];
    if (first == '#')
	first = (++s)[0];
    prep = strtol(s, &ptr, 10);
    if (*ptr == '\0') {
	free_str(s);
	if (!isdigit(first) || prep >= NPREPS)
	    return PREP_NONE;
	else
	    return prep;
    }
    if ((ptr = strchr(s, '/')) != '\0')
	*ptr = '\0';

    argv = parse_into_words(s, &argc);
    prep = db_find_prep(argc, argv, 0, 0);
    free_str(s);
    return prep;
}
