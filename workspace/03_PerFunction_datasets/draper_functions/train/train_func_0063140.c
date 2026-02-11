maybe_print_lad_warning (const MODEL *pmod, PRN *prn)
{
    if (gretl_model_get_int(pmod, "nonunique")) {
	pputs(prn, A_("Warning: solution is probably not unique"));
	pputc(prn, '\n');
    }
}
