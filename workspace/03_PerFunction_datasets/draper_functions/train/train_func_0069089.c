kcmss_close(krb5_context context,
	    krb5_ccache id)
{
    kcm_ccache c = KCMCACHE(id);

    KCM_ASSERT_VALID(c);

    id->data.data = NULL;
    id->data.length = 0;

    return 0;
}
