parse_as_each_loop (LOOPSET *loop, DATASET *dset, char *s)
{
    char ivar[VNAMELEN] = {0};
    int done = 0;
    int nf, err = 0;


    if (*s == '\0') {
	return E_PARSE;
    }

    s += strspn(s, " ");

#if LOOP_DEBUG
    fprintf(stderr, "parse_as_each_loop: s = '%s'\n", s);
#endif


    if (gretl_scan_varname(s, ivar) != 1) {
	return E_PARSE;
    }

    s += strlen(ivar);
    nf = count_each_fields(s);

#if LOOP_DEBUG
    fprintf(stderr, " number of fields = %d\n", nf);
#endif

    if (nf == 0) {
	return E_PARSE;
    }

    if (nf <= 3 && strstr(s, "..") != NULL) {

	err = each_strings_from_list_of_vars(loop, dset, s, &nf,
					     DOTTED_LIST);
	done = 1;
    } else if (nf == 1 && strchr(s, '*')) {
	err = each_strings_from_list_of_vars(loop, dset, s, &nf,
					     WILDCARD_LIST);
	done = (err == 0);
    }

    if (!done && nf == 1) {

	err = list_loop_setup(loop, s, &nf);
	done = (err == 0);
    }

    if (!done) {

	loop->eachstrs = gretl_string_split_quoted(s, &nf, NULL, &err);
    }

    if (!err) {
	loop->type = EACH_LOOP;
	loop->init.val = 1;
	loop->final.val = nf;
	err = loop_attach_index_var(loop, ivar, dset);
    }

#if LOOP_DEBUG
    fprintf(stderr, "parse_as_each_loop: final.val=%g\n", loop->final.val);
#endif

    return err;
}
