Perl_sv_catsv_flags(pTHX_ SV *const dsv, SV *const ssv, const I32 flags)
{
    dVAR;

    PERL_ARGS_ASSERT_SV_CATSV_FLAGS;

    if (ssv) {
	STRLEN slen;
	const char *spv = SvPV_flags_const(ssv, slen, flags);
	if (spv) {
            if (flags & SV_GMAGIC)
                SvGETMAGIC(dsv);
	    sv_catpvn_flags(dsv, spv, slen,
			    DO_UTF8(ssv) ? SV_CATUTF8 : SV_CATBYTES);
            if (flags & SV_SMAGIC)
                SvSETMAGIC(dsv);
        }
    }
}
