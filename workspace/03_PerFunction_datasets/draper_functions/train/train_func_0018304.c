_gss_spnego_context_time
           (OM_uint32 *minor_status,
            gss_const_ctx_id_t context_handle,
            OM_uint32 *time_rec
           )
{
    gssspnego_ctx ctx;
    *minor_status = 0;

    if (context_handle == GSS_C_NO_CONTEXT) {
	return GSS_S_NO_CONTEXT;
    }

    ctx = (gssspnego_ctx)context_handle;

    if (ctx->negotiated_ctx_id == GSS_C_NO_CONTEXT) {
	return GSS_S_NO_CONTEXT;
    }

    return gss_context_time(minor_status,
			    ctx->negotiated_ctx_id,
			    time_rec);
}
