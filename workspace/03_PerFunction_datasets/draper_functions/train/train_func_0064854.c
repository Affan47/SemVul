_krb5_kcm_get_initial_ticket(krb5_context context,
			     krb5_ccache id,
			     krb5_principal server,
			     krb5_keyblock *key)
{
    krb5_kcmcache *k = KCMCACHE(id);
    krb5_error_code ret;
    krb5_storage *request;

    ret = krb5_kcm_storage_request(context, KCM_OP_GET_INITIAL_TICKET, &request);
    if (ret)
	return ret;

    ret = krb5_store_stringz(request, k->name);
    if (ret) {
	krb5_storage_free(request);
	return ret;
    }

    ret = krb5_store_int8(request, (server == NULL) ? 0 : 1);
    if (ret) {
	krb5_storage_free(request);
	return ret;
    }

    if (server != NULL) {
	ret = krb5_store_principal(request, server);
	if (ret) {
	    krb5_storage_free(request);
	    return ret;
	}
    }

    ret = krb5_store_keyblock(request, *key);
    if (ret) {
	krb5_storage_free(request);
	return ret;
    }

    ret = krb5_kcm_call(context, request, NULL, NULL);

    krb5_storage_free(request);
    return ret;
}
