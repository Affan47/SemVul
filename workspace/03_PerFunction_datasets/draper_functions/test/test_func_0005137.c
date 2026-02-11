process_tconvert_info (csvjoin *jspec,
				  const char *tconvcols,
				  const char *tconvfmt,
				  const char *keyfmt)
{
    int *list = NULL;
    char **names = NULL;
    char **fmts = NULL;
    const char *colname;
    const char *tkeyfmt = NULL;
    char *tkeyname = NULL;
    int nnames = 0;
    int i, j, err = 0;

    names = gretl_string_split(tconvcols, &nnames, " ,");
    if (names == NULL) {
	err = E_ALLOC;
    }


    for (i=0; i<nnames && !err; i++) {
	for (j=0; j<JOIN_MAXCOL; j++) {
	    colname = jspec->colnames[j];
	    if (colname != NULL && !strcmp(names[i], colname)) {
		gretl_list_append_term(&list, j);
		if (list == NULL) {
		    err = E_ALLOC;
		} else if (*keyfmt != '\0' && j == JOIN_KEY) {


		    tkeyfmt = keyfmt;
		    tkeyname = names[i];
		}
		break;
	    }
	}
    }


    if (!err && list != NULL && (tconvfmt != NULL || tkeyfmt != NULL)) {
	char const *tmp[2] = {tconvfmt, tkeyfmt};

	err = make_time_formats_array(tmp, &fmts);
    }

#if CDEBUG
    printlist(list, "timeconv list");
#endif

    if (!err && list != NULL) {
	timeconv_map_set(nnames, names, tkeyname, fmts);
    }

    if (err) {

	strings_array_free(names, nnames);
	free(list);
    } else {
	jspec->timecols = list;
    }

    return err;
}
