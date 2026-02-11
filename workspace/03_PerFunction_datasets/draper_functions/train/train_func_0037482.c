kcm_move(krb5_context context, krb5_ccache from, krb5_ccache to)
{
    krb5_error_code ret;
    krb5_kcmcache *oldk = KCMCACHE(from);
    krb5_kcmcache *newk = KCMCACHE(to);
    krb5_storage *request;

    ret = krb5_kcm_storage_request(context, KCM_OP_MOVE_CACHE, &request);
    if (ret)
	return ret;

    ret = krb5_store_stringz(request, oldk->name);
    if (ret) {
	krb5_storage_free(request);
	return ret;
    }

    ret = krb5_store_stringz(request, newk->name);
    if (ret) {
	krb5_storage_free(request);
	return ret;
    }
    ret = krb5_kcm_call(context, request, NULL, NULL);

    krb5_storage_free(request);
    return ret;
}
