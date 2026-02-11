get_service_keyblock
        (OM_uint32 *minor_status,
	 gsskrb5_ctx ctx,
	 gss_buffer_set_t *data_set)
{
    krb5_storage *sp = NULL;
    krb5_data data;
    OM_uint32 maj_stat = GSS_S_COMPLETE;
    krb5_error_code ret = EINVAL;

    sp = krb5_storage_emem();
    if (sp == NULL) {
	_gsskrb5_clear_status();
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    HEIMDAL_MUTEX_lock(&ctx->ctx_id_mutex);
    if (ctx->service_keyblock == NULL) {
	HEIMDAL_MUTEX_unlock(&ctx->ctx_id_mutex);
	krb5_storage_free(sp);
	_gsskrb5_set_status(EINVAL, "No service keyblock on gssapi context");
	*minor_status = EINVAL;
	return GSS_S_FAILURE;
    }

    krb5_data_zero(&data);

    ret = krb5_store_keyblock(sp, *ctx->service_keyblock);

    HEIMDAL_MUTEX_unlock(&ctx->ctx_id_mutex);

    if (ret)
	goto out;

    ret = krb5_storage_to_data(sp, &data);
    if (ret)
	goto out;

    {
	gss_buffer_desc value;

	value.length = data.length;
	value.value = data.data;

	maj_stat = gss_add_buffer_set_member(minor_status,
					     &value,
					     data_set);
    }

out:
    krb5_data_free(&data);
    if (sp)
	krb5_storage_free(sp);
    if (ret) {
	*minor_status = ret;
	maj_stat = GSS_S_FAILURE;
    }
    return maj_stat;
}
