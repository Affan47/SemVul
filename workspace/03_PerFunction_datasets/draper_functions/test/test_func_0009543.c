mcc_gen_new(krb5_context context, krb5_ccache *id)
{
    krb5_mcache *m;

    m = mcc_alloc(NULL);

    if (m == NULL) {
	krb5_set_error_message(context, KRB5_CC_NOMEM,
			       N_("malloc: out of memory", ""));
	return KRB5_CC_NOMEM;
    }

    (*id)->data.data = m;
    (*id)->data.length = sizeof(*m);

    return 0;
}
