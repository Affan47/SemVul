Perl_fbm_compile(pTHX_ SV *sv, U32 flags)
{
    dVAR;
    const U8 *s;
    STRLEN i;
    STRLEN len;
    STRLEN rarest = 0;
    U32 frequency = 256;
    MAGIC *mg;

    PERL_ARGS_ASSERT_FBM_COMPILE;

    if (isGV_with_GP(sv))
	return;

    if (SvVALID(sv))
	return;

    if (flags & FBMcf_TAIL) {
	MAGIC * const mg = SvUTF8(sv) && SvMAGICAL(sv) ? mg_find(sv, PERL_MAGIC_utf8) : NULL;
	sv_catpvs(sv, "\n");
	if (mg && mg->mg_len >= 0)
	    mg->mg_len++;
    }
    s = (U8*)SvPV_force_mutable(sv, len);
    if (len == 0)
	return;
    SvUPGRADE(sv, SVt_PVMG);
    SvIOK_off(sv);
    SvNOK_off(sv);
    SvVALID_on(sv);


    assert(!mg_find(sv, PERL_MAGIC_bm));
    mg = sv_magicext(sv, NULL, PERL_MAGIC_bm, &PL_vtbl_bm, NULL, 0);
    assert(mg);

    if (len > 2) {


	const U8 mlen = (len>255) ? 255 : (U8)len;
	const unsigned char *const sb = s + len - mlen;
	U8 *table;

	Newx(table, 256, U8);
	memset((void*)table, mlen, 256);
	mg->mg_ptr = (char *)table;
	mg->mg_len = 256;

	s += len - 1;
	i = 0;
	while (s >= sb) {
	    if (table[*s] == mlen)
		table[*s] = (U8)i;
	    s--, i++;
	}
    }

    s = (const unsigned char*)(SvPVX_const(sv));
    for (i = 0; i < len; i++) {
	if (PL_freq[s[i]] < frequency) {
	    rarest = i;
	    frequency = PL_freq[s[i]];
	}
    }
    BmRARE(sv) = s[rarest];
    BmPREVIOUS(sv) = rarest;
    BmUSEFUL(sv) = 100;
    if (flags & FBMcf_TAIL)
	SvTAIL_on(sv);
    DEBUG_r(PerlIO_printf(Perl_debug_log, "rarest char %c at %"UVuf"\n",
			  BmRARE(sv), BmPREVIOUS(sv)));
}
