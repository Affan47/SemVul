Perl_cv_ckproto_len_flags(pTHX_ const CV *cv, const GV *gv, const char *p,
		    const STRLEN len, const U32 flags)
{
    const char * const cvp = SvROK(cv) ? "" : CvPROTO(cv);
    const STRLEN clen = CvPROTOLEN(cv);

    PERL_ARGS_ASSERT_CV_CKPROTO_LEN_FLAGS;

    if (((!p != !cvp)
	|| (p && (
		  (flags & SVf_UTF8) == SvUTF8(cv)
		   ? len != clen || memNE(cvp, p, len)
		   : flags & SVf_UTF8
		      ? bytes_cmp_utf8((const U8 *)cvp, clen,
				       (const U8 *)p, len)
		      : bytes_cmp_utf8((const U8 *)p, len,
				       (const U8 *)cvp, clen)
		 )
	   )
        )
	 && ckWARN_d(WARN_PROTOTYPE)) {
	SV* const msg = sv_newmortal();
	SV* name = NULL;

	if (gv)
	{
	  if (isGV(gv))
	    gv_efullname3(name = sv_newmortal(), gv, NULL);
	  else if (SvPOK(gv) && *SvPVX((SV *)gv) == '&')
	    name = newSVpvn_flags(SvPVX((SV *)gv)+1, SvCUR(gv)-1,
				  SvUTF8(gv)|SVs_TEMP);
	  else name = (SV *)gv;
	}
	sv_setpvs(msg, "Prototype mismatch:");
	if (name)
	    Perl_sv_catpvf(aTHX_ msg, " sub %"SVf, SVfARG(name));
	if (cvp)
	    Perl_sv_catpvf(aTHX_ msg, " (%"SVf")",
		SVfARG(newSVpvn_flags(cvp,clen, SvUTF8(cv)|SVs_TEMP))
	    );
	else
	    sv_catpvs(msg, ": none");
	sv_catpvs(msg, " vs ");
	if (p)
	    Perl_sv_catpvf(aTHX_ msg, "(%"SVf")", SVfARG(newSVpvn_flags(p, len, flags | SVs_TEMP)));
	else
	    sv_catpvs(msg, "none");
	Perl_warner(aTHX_ packWARN(WARN_PROTOTYPE), "%"SVf, SVfARG(msg));
    }
}
