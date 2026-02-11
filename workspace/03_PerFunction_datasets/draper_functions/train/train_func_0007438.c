_gss_spnego_wrap
           (OM_uint32 * minor_status,
            gss_const_ctx_id_t context_handle,
            int conf_req_flag,
            gss_qop_t qop_req,
            const gss_buffer_t input_message_buffer,
            int * conf_state,
            gss_buffer_t output_message_buffer
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

    return gss_wrap(minor_status,
		    ctx->negotiated_ctx_id,
		    conf_req_flag,
		    qop_req,
		    input_message_buffer,
		    conf_state,
		    output_message_buffer);
}
