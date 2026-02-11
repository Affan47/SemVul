make_tex_prn (int ID, char *fname,
			  int eqn, int doc, int *err)
{
    char texfile[FILENAME_MAX];
    PrnFormat fmt = GRETL_FORMAT_TEX;
    PRN *prn;

    if (*fname == '\0') {
	sprintf(texfile, "%s%s_%d.tex", gretl_workdir(),
		(eqn)? "equation" : "model", ID);
	strcpy(fname, texfile);
    } else {
	gretl_maybe_switch_dir(fname);
	strcpy(texfile, fname);
    }

    prn = gretl_print_new_with_filename(texfile, err);

    if (prn != NULL) {
	if (eqn) {
	    fmt |= GRETL_FORMAT_EQN;
	}
	if (doc) {
	    fmt |= GRETL_FORMAT_DOC;
	}
	gretl_print_set_format(prn, fmt);
    }

    return prn;
}
