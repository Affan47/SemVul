Perl_cop_fetch_label(pTHX_ COP *const cop, STRLEN *len, U32 *flags) {
    struct refcounted_he *const chain = cop->cop_hints_hash;

    PERL_ARGS_ASSERT_COP_FETCH_LABEL;

    if (!chain)
	return NULL;
#ifdef USE_ITHREADS
    if (chain->refcounted_he_keylen != 1)
	return NULL;
    if (*REF_HE_KEY(chain) != ':')
	return NULL;
#else
    if ((STRLEN)HEK_LEN(chain->refcounted_he_hek) != 1)
	return NULL;
    if (*HEK_KEY(chain->refcounted_he_hek) != ':')
	return NULL;
#endif


    if ((chain->refcounted_he_data[0] & HVrhek_typemask) != HVrhek_PV
	&& (chain->refcounted_he_data[0] & HVrhek_typemask) != HVrhek_PV_UTF8)
	return NULL;

    if (len)
	*len = chain->refcounted_he_val.refcounted_he_u_len;
    if (flags) {
	*flags = ((chain->refcounted_he_data[0] & HVrhek_typemask)
		  == HVrhek_PV_UTF8) ? SVf_UTF8 : 0;
    }
    return chain->refcounted_he_data + 1;
}
