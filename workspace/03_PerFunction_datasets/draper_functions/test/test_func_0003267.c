Perl_av_iter_p(pTHX_ AV *av) {
    MAGIC *const mg = get_aux_mg(av);

    PERL_ARGS_ASSERT_AV_ITER_P;
    assert(SvTYPE(av) == SVt_PVAV);

#if IVSIZE == I32SIZE
    return (IV *)&(mg->mg_len);
#else
    if (!mg->mg_ptr) {
	IV *temp;
	mg->mg_len = IVSIZE;
	Newxz(temp, 1, IV);
	mg->mg_ptr = (char *) temp;
    }
    return (IV *)mg->mg_ptr;
#endif
}
