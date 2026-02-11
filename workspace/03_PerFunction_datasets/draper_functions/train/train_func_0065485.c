PerlCallbackSub (struct _perlcontext *cp, char **result, Size_t *len, AV *args)
{
	int rc = SASL_OK;

	int count;
	SV *rsv;

	if (result == NULL)
		return SASL_FAIL;

	if (*result != NULL)
		free(*result);

	if (len == NULL)
		return SASL_FAIL;

	__DEBUG("Callback Callback");

	if (cp->func == NULL)
	{
		if (cp->param == NULL)
			rc = SASL_FAIL;
		else {
			_DEBUG("PV: %s",SvPV(cp->param,*len));
			*result = strdup(SvPV(cp->param,*len));
		}
	}
	else
	{

		dSP;

		ENTER ;
		SAVETMPS ;

		PUSHMARK(SP);
		if (cp->param)
			XPUSHs( cp->param );


		if (args != NULL)
			while (av_len(args) >= 0)
				XPUSHs(av_pop(args));
		PUTBACK ;

		count = call_sv(cp->func, G_SCALAR);


		SPAGAIN;

		_DEBUG("Count of retvals: %d",count);

		if (count != 1)
			rc = SASL_FAIL;
		else
		{
			rsv = POPs;
			if (SvOK(rsv)) {
				if ( (*result = strdup(SvPV(rsv, *len))) == NULL)
					rc = SASL_FAIL;
			} else {
				*result = strdup("");
			}
		}

		PUTBACK ;


		FREETMPS ;
		LEAVE ;
	}
	return rc;
}
