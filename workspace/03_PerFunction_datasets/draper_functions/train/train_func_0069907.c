PerlIO_parse_layers(pTHX_ PerlIO_list_t *av, const char *names)
{
    dVAR;
    if (names) {
	const char *s = names;
	while (*s) {
	    while (isSPACE(*s) || *s == ':')
		s++;
	    if (*s) {
		STRLEN llen = 0;
		const char *e = s;
		const char *as = NULL;
		STRLEN alen = 0;
		if (!isIDFIRST(*s)) {


		    const char q = ((*s == '\'') ? '"' : '\'');
		    Perl_ck_warner(aTHX_ packWARN(WARN_LAYER),
				   "Invalid separator character %c%c%c in PerlIO layer specification %s",
				   q, *s, q, s);
		    SETERRNO(EINVAL, LIB_INVARG);
		    return -1;
		}
		do {
		    e++;
		} while (isWORDCHAR(*e));
		llen = e - s;
		if (*e == '(') {
		    int nesting = 1;
		    as = ++e;
		    while (nesting) {
			switch (*e++) {
			case ')':
			    if (--nesting == 0)
				alen = (e - 1) - as;
			    break;
			case '(':
			    ++nesting;
			    break;
			case '\\':


			    if (*e++) {
				break;
			    }


			case '\0':
			    e--;
			    Perl_ck_warner(aTHX_ packWARN(WARN_LAYER),
					   "Argument list not closed for PerlIO layer \"%.*s\"",
					   (int) (e - s), s);
			    return -1;
			default:


			    break;
			}
		    }
		}
		if (e > s) {
		    PerlIO_funcs * const layer =
			PerlIO_find_layer(aTHX_ s, llen, 1);
		    if (layer) {
			SV *arg = NULL;
			if (as)
			    arg = newSVpvn(as, alen);
			PerlIO_list_push(aTHX_ av, layer,
					 (arg) ? arg : &PL_sv_undef);
			SvREFCNT_dec(arg);
		    }
		    else {
			Perl_ck_warner(aTHX_ packWARN(WARN_LAYER), "Unknown PerlIO layer \"%.*s\"",
				       (int) llen, s);
			return -1;
		    }
		}
		s = e;
	    }
	}
    }
    return 0;
}
