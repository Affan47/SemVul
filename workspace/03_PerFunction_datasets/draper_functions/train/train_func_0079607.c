print_heckit_stats (const MODEL *pmod, PRN *prn)
{
    int totobs = gretl_model_get_int(pmod, "totobs");
    int cenobs = totobs - pmod->nobs;
    double cenpc = (100.0 * cenobs) / totobs;

    ensure_vsep(prn);

    if (plain_format(prn)) {
	pprintf(prn, "%s: %d\n", _("Total observations"), totobs);
	pprintf(prn, "%s: %d (%.1f%%)\n", _("Censored observations"),
		cenobs, cenpc);
	pputc(prn, '\n');
    } else if (rtf_format(prn)) {
	pprintf(prn, RTFTAB "%s: %d\n", A_("Total observations"), totobs);
	pprintf(prn, RTFTAB "%s: %d (%.1f%%)\n", A_("Censored observations"),
		cenobs, cenpc);
    } else if (tex_format(prn)) {
	pprintf(prn, "%s: %d \\\\\n", A_("Total observations"), totobs);
	pprintf(prn, "%s: %d (%.1f\\%%) \\\\\n", A_("Censored observations"),
		cenobs, cenpc);
    }
}
