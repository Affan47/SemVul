gss_accept_sec_context_spnego
           (OM_uint32 * minor_status,
            gss_ctx_id_t * context_handle,
            const gss_cred_id_t acceptor_cred_handle,
            const gss_buffer_t input_token_buffer,
            const gss_channel_bindings_t input_chan_bindings,
            gss_name_t * src_name,
            gss_OID * mech_type,
            gss_buffer_t output_token,
            OM_uint32 * ret_flags,
            OM_uint32 * time_rec,
            gss_cred_id_t * delegated_cred_handle)
{
   NegTokenInit init_token;
   OM_uint32 major_status;
   OM_uint32 minor_status2;
   gss_buffer_desc ibuf, obuf;
   gss_buffer_t ot = NULL;
   unsigned char *buf;
   size_t buf_size;
   size_t len, taglen, ni_len;
   int found = 0;
   int ret, i;

   memset(&init_token, 0, sizeof(init_token));

   ret = gssapi_spnego_decapsulate(minor_status, input_token_buffer,
	 			   &buf, &buf_size, GSS_SPNEGO_MECH);
   if (ret)
      return ret;

   ret = der_match_tag_and_length(buf, buf_size, KERB_CTXT, CONS,
	 			  0, &len, &taglen);
   if (ret)
      return ret;

   ret = decode_NegTokenInit(buf + taglen, len, &init_token, &ni_len);
   if (ret) {
      *minor_status = EINVAL;
      return GSS_S_DEFECTIVE_TOKEN;
   }

   if (init_token.mechTypes == NULL)
      return send_reject (minor_status, output_token);

   for (i = 0; !found && i < init_token.mechTypes->len; ++i) {
      unsigned char mechbuf[17];
      size_t mech_len;

      ret = der_put_oid (mechbuf + sizeof(mechbuf) - 1,
                         sizeof(mechbuf),
                         &init_token.mechTypes->val[i],
                         &mech_len);
      if (ret)
          return GSS_S_DEFECTIVE_TOKEN;
      if (mech_len == GSS_KRB5_MECH->length
          && memcmp(GSS_KRB5_MECH->elements,
                    mechbuf + sizeof(mechbuf) - mech_len,
                    mech_len) == 0)
          found = 1;
   }

   if (!found)
      return send_reject (minor_status, output_token);

   if (init_token.mechToken != NULL) {
      ibuf.length = init_token.mechToken->length;
      ibuf.value  = init_token.mechToken->data;

      major_status = gss_accept_sec_context(minor_status,
	    				    context_handle,
					    acceptor_cred_handle,
					    &ibuf,
					    input_chan_bindings,
					    src_name,
					    mech_type,
					    &obuf,
					    ret_flags,
					    time_rec,
					    delegated_cred_handle);
      if (GSS_ERROR(major_status)) {
	 send_reject (&minor_status2, output_token);
	 return major_status;
      }
      ot = &obuf;
   }

   ret = send_accept (&minor_status2, output_token, ot);
   if (ot != NULL)
      gss_release_buffer(&minor_status2, ot);

   return ret;
}
