Perl_sv_pos_u2b_flags(pTHX_ SV *const sv, STRLEN uoffset, STRLEN *const lenp,
		      U32 flags)
{
    const U8 *start;
    STRLEN len;
    STRLEN boffset;

    PERL_ARGS_ASSERT_SV_POS_U2B_FLAGS;

    start = (U8*)SvPV_flags(sv, len, flags);
    if (len) {
	const U8 * const send = start + len;
	MAGIC *mg = NULL;
	boffset = sv_pos_u2b_cached(sv, &mg, start, send, uoffset, 0, 0);

	if (lenp
	    && *lenp
) {

	    const STRLEN uoffset2 = uoffset + *lenp;
	    const STRLEN boffset2
		= sv_pos_u2b_cached(sv, &mg, start, send, uoffset2,
				      uoffset, boffset) - boffset;

	    *lenp = boffset2;
	}
    } else {
	if (lenp)
	    *lenp = 0;
	boffset = 0;
    }

    return boffset;
}
