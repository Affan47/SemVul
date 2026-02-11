purple_perl_util_url_cb(PurpleUtilFetchUrlData *url_data, void *user_data,
                        const gchar *url_text, size_t size,
                        const gchar *error_message)
{
	SV *sv = (SV *)user_data;
	dSP;
	ENTER;
	SAVETMPS;
	PUSHMARK(SP);

	XPUSHs(sv_2mortal(newSVpvn(url_text, size)));
	PUTBACK;

	call_sv(sv, G_EVAL | G_SCALAR);
	SPAGAIN;


	SvREFCNT_dec(sv);

	PUTBACK;
	FREETMPS;
	LEAVE;
}
