Perl_pregfree2(pTHX_ REGEXP *rx)
{
    dVAR;
    struct regexp *const r = ReANY(rx);
    GET_RE_DEBUG_FLAGS_DECL;

    PERL_ARGS_ASSERT_PREGFREE2;

    if (r->mother_re) {
        ReREFCNT_dec(r->mother_re);
    } else {
        CALLREGFREE_PVT(rx);
        SvREFCNT_dec(RXp_PAREN_NAMES(r));
	Safefree(r->xpv_len_u.xpvlenu_pv);
    }
    if (r->substrs) {
        SvREFCNT_dec(r->anchored_substr);
        SvREFCNT_dec(r->anchored_utf8);
        SvREFCNT_dec(r->float_substr);
        SvREFCNT_dec(r->float_utf8);
	Safefree(r->substrs);
    }
    RX_MATCH_COPY_FREE(rx);
#ifdef PERL_ANY_COW
    SvREFCNT_dec(r->saved_copy);
#endif
    Safefree(r->offs);
    SvREFCNT_dec(r->qr_anoncv);
    rx->sv_u.svu_rx = 0;
}
