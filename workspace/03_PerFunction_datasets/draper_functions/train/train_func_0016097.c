perl_load(script_t *scr)
{
	int mask = 0;
	perl_private_t *p;

	char *error;
	int retcount;
	SV *ret;

	dSP;
	ENTER;
	SAVETMPS;
	PUSHMARK(SP);
	XPUSHs(sv_2mortal(new_pv(scr->path)));
	XPUSHs(sv_2mortal(new_pv(scr->name)));
	PUTBACK;

	retcount = perl_call_pv("Ekg2::Core::eval_file",
				G_EVAL|G_SCALAR);
	SPAGAIN;
	error = NULL;
	if (SvTRUE(ERRSV)) {
		error = SvPV(ERRSV, PL_na);
		print("script_error", error);

	} else if (retcount > 0) {
		ret = POPs;
		mask = SvIV(ret);
	}

	PUTBACK;
	FREETMPS;
	LEAVE;

	p = xmalloc(sizeof(perl_private_t));

	script_private_set(scr, p);

	return mask;

}
