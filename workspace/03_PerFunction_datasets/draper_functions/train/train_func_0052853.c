print_model_stats_table (const double *stats,
				     const char **names,
				     int ns, PRN *prn)
{
    char tmp1[32], tmp2[32];
    int i;

    if (plain_format(prn)) {
	pputc(prn, '\n');
    } else if (tex_format(prn)) {
	pputs(prn, "\\medskip\n\n");
	pputs(prn, "\\begin{tabular}{lr@{.}l}\n");
    }

    for (i=0; i<ns; i++) {
	if (plain_format(prn)) {
	    plain_print_double(tmp1, GRETL_DIGITS, stats[i], prn);
	    pprintf(prn, "  %s = %s\n", names[i], tmp1);
	} else if (tex_format(prn)) {
	    tex_escape_special(tmp1, names[i]);
	    tex_rl_double(stats[i], tmp2);
	    pprintf(prn, "%s & %s \\\\\n", tmp1, tmp2);
	} else if (rtf_format(prn)) {
	    pprintf(prn, RTFTAB "%s = %g\n", names[i], stats[i]);
	} else if (csv_format(prn)) {
	    pprintf(prn, "\"%s\"%c%.15g\n", names[i], prn_delim(prn), stats[i]);
	}
    }

    if (tex_format(prn)) {
	pputs(prn, "\\end{tabular}");
    }
}
