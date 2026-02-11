_gss_ntlm_inquire_sec_context_by_oid(OM_uint32 *minor_status,
				     gss_const_ctx_id_t context_handle,
				     const gss_OID desired_object,
				     gss_buffer_set_t *data_set)
{
    ntlm_ctx ctx = (ntlm_ctx)context_handle;

    if (ctx == NULL) {
	*minor_status = 0;
	return GSS_S_NO_CONTEXT;
    }

    if (gss_oid_equal(desired_object, GSS_NTLM_GET_SESSION_KEY_X) ||
        gss_oid_equal(desired_object, GSS_C_INQ_SSPI_SESSION_KEY)) {
	gss_buffer_desc value;

	value.length = ctx->sessionkey.length;
	value.value = ctx->sessionkey.data;

	return gss_add_buffer_set_member(minor_status,
					 &value,
					 data_set);
    } else if (gss_oid_equal(desired_object, GSS_C_INQ_WIN2K_PAC_X)) {
	if (ctx->pac.length == 0) {
	    *minor_status = ENOENT;
	    return GSS_S_FAILURE;
	}

	return gss_add_buffer_set_member(minor_status,
					 &ctx->pac,
					 data_set);

    } else if (gss_oid_equal(desired_object, GSS_C_NTLM_AVGUEST)) {
	gss_buffer_desc value;
	uint32_t num;

	if (ctx->kcmflags & KCM_NTLM_FLAG_AV_GUEST)
	    num = 1;
	else
	    num = 0;

	value.length = sizeof(num);
	value.value = &num;

	return gss_add_buffer_set_member(minor_status,
					 &value,
					 data_set);
    } else {
	*minor_status = 0;
	return GSS_S_FAILURE;
    }
}
