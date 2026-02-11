epstool_dcs2_check_files(Doc *doc, OPT *opt)
{
    int code = 0;
    int i;
    CDSC *dsc = doc->dsc;
    GFile *f;
    const char *fname;
    const char **renamed1 = NULL;
    for (i=1; (i<(int)dsc->page_count); i++) {

	fname = dsc_find_platefile(dsc, i);
	if (fname) {
	    TCHAR wfname[MAXSTR];
	    narrow_to_cs(wfname, (int)(sizeof(wfname)/sizeof(TCHAR)-1),
		fname, (int)strlen(fname)+1);
	    if ((f = gfile_open(wfname, gfile_modeRead)) != (GFile *)NULL) {
		gfile_close(f);
	    }
	    else {
		if (!opt->missing_separations)
		    code = -1;
		if (!opt->quiet)
		    app_msgf(doc->app,
		    "Separation \042%s\042 is missing file \042%s\042\n",
			dsc->page[i].label, fname);
	    }
	}
	else {
	    if (dsc->page[i].end <= dsc->page[i].begin) {
		if (!opt->quiet)
	            app_msgf(doc->app,
			"Separation \042%s\042 is empty\n",
			dsc->page[i].label);
		if (!opt->missing_separations)
		    code = -1;
	    }
	}
    }

    renamed1 = (const char **)malloc(sizeof(const char *) * dsc->page_count);
    if (renamed1 != NULL) {
	if (rename_separations(dsc, opt->rename_sep, renamed1) != 0) {
	    code = -1;
	    if (!opt->quiet)
	      app_msgf(doc->app, "Duplicate separations are not permitted.\n");
	}
	free((void *)renamed1);
    }

    return code;
}
