acc_gen_new(krb5_context context, krb5_ccache *id)
{
    krb5_error_code ret;
    krb5_acc *a;

    ret = acc_alloc(context, id);
    if (ret)
	return ret;

    a = ACACHE(*id);

    a->ccache = NULL;
    a->cache_name = NULL;

    return 0;
}
