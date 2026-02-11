rtf_print_row_spec (int ncols, int type, PRN *prn)
{
    int j;

    if (type == RTF_TRAILER) {
	pputc(prn, '{');
    }

    pputs(prn, "\\trowd\\trautofit1\n\\intbl\n");
    for (j=1; j<=ncols; j++) {
	pprintf(prn, "\\cellx%d\n", j);
    }

    if (type == RTF_TRAILER) {
	pputs(prn, "\\row }\n");
    }
}
