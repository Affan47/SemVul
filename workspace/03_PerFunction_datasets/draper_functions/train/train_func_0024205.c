gss_inquire_sec_context_by_oid (OM_uint32 *minor_status,
	                        gss_const_ctx_id_t context_handle,
	                        const gss_OID desired_object,
	                        gss_buffer_set_t *data_set)
{
	struct _gss_context	*ctx = (struct _gss_context *) context_handle;
	OM_uint32		major_status;
	gssapi_mech_interface	m;

	*minor_status = 0;
	*data_set = GSS_C_NO_BUFFER_SET;
	if (ctx == NULL)
		return GSS_S_NO_CONTEXT;


	m = ctx->gc_mech;

	if (m == NULL)
		return GSS_S_BAD_MECH;

	if (m->gm_inquire_sec_context_by_oid != NULL) {
		major_status = m->gm_inquire_sec_context_by_oid(minor_status,
		    ctx->gc_ctx, desired_object, data_set);
		if (major_status != GSS_S_COMPLETE)
			_gss_mg_error(m, major_status, *minor_status);
	} else
		major_status = GSS_S_BAD_MECH;

	return major_status;
}
