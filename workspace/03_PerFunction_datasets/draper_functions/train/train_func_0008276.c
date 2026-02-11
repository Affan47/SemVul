kcm_op_chmod(krb5_context context,
	     kcm_client *client,
	     kcm_operation opcode,
	     krb5_storage *request,
	     krb5_storage *response)
{
    uint16_t mode;
    krb5_error_code ret;
    kcm_ccache ccache;
    char *name;

    ret = krb5_ret_stringz(request, &name);
    if (ret)
	return ret;

    KCM_LOG_REQUEST_NAME(context, client, opcode, name);

    ret = krb5_ret_uint16(request, &mode);
    if (ret) {
	free(name);
	return ret;
    }

    ret = kcm_ccache_resolve_client(context, client, opcode,
				    name, &ccache);
    if (ret) {
	free(name);
	return ret;
    }

    ret = kcm_chmod(context, client, ccache, mode);

    free(name);
    kcm_release_ccache(context, ccache);

    return ret;
}
