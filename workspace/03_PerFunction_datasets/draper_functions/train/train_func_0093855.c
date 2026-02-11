write_stata_io_file (void)
{
    static int written;

    if (!written) {
	const char *dotdir = gretl_dotdir();
	gchar *fname;
	FILE *fp;

	fname = g_strdup_printf("%sgretl_export.ado", dotdir);
	fp = gretl_fopen(fname, "w");
	g_free(fname);

	if (fp == NULL) {
	    return E_FOPEN;
	} else {
	    fputs("program define gretl_export\n", fp);

	    fputs("version 8.2\n", fp);
	    fputs("local matrix `1'\n", fp);
	    fputs("local fname `2'\n", fp);
	    fputs("tempname myfile\n", fp);
	    fputs("file open `myfile' using \"`fname'\", "
		  "write text replace\n", fp);
	    fputs("local nrows = rowsof(`matrix')\n", fp);
	    fputs("local ncols = colsof(`matrix')\n", fp);
	    fputs("file write `myfile' %8.0g (`nrows') %8.0g (`ncols') _n\n", fp);
	    fputs("forvalues r=1/`nrows' {\n", fp);
	    fputs("  forvalues c=1/`ncols' {\n", fp);
	    fputs("    file write `myfile' %15.0e (`matrix'[`r',`c']) _n\n", fp);
	    fputs("  }\n", fp);
	    fputs("}\n", fp);
	    fputs("file close `myfile'\n", fp);
	    fputs("end\n", fp);

	    fclose(fp);
	    written = 1;
	}
    }

    return 0;
}
