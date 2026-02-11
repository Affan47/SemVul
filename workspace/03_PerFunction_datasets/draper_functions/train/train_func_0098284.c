gss_init_sec_context_spnego(OM_uint32 *minor_status,
			    const gss_cred_id_t initiator_cred_handle,
			    gss_ctx_id_t *context_handle,
			    const gss_name_t target_name,
			    const gss_OID mech_type,
			    OM_uint32 req_flags,
			    OM_uint32 time_req,
			    const gss_channel_bindings_t input_chan_bindings,
			    const gss_buffer_t input_token,
			    gss_OID *actual_mech_type,
			    gss_buffer_t output_token,
			    OM_uint32 *ret_flags,
			    OM_uint32 *time_rec)
{


	if (input_token == GSS_C_NO_BUFFER || input_token->length == 0U)
		return (spnego_initial(minor_status,
				       initiator_cred_handle,
				       context_handle,
				       target_name,
				       mech_type,
				       req_flags,
				       time_req,
				       input_chan_bindings,
				       input_token,
				       actual_mech_type,
				       output_token,
				       ret_flags,
				       time_rec));
	else
		return (spnego_reply(minor_status,
				     initiator_cred_handle,
				     context_handle,
				     target_name,
				     mech_type,
				     req_flags,
				     time_req,
				     input_chan_bindings,
				     input_token,
				     actual_mech_type,
				     output_token,
				     ret_flags,
				     time_rec));
}
