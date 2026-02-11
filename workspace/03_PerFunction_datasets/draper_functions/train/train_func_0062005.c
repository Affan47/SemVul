_gss_spnego_get_mic
           (OM_uint32 *minor_status,
            gss_const_ctx_id_t context_handle,
            gss_qop_t qop_req,
            const gss_buffer_t message_buffer,
            gss_buffer_t message_token
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

    return gss_get_mic(minor_status, ctx->negotiated_ctx_id,
		       qop_req, message_buffer, message_token);
}
