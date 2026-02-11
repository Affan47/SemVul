tds_gss_continue(TDSSOCKET * tds, struct tds_gss_auth *auth, gss_buffer_desc *token_ptr)
{
	gss_buffer_desc send_tok;
	OM_uint32 maj_stat, min_stat;
	OM_uint32 ret_flags;
	int gssapi_flags;

	auth->last_stat = GSS_S_COMPLETE;

	send_tok.value = NULL;
	send_tok.length = 0;


	gssapi_flags = GSS_C_MUTUAL_FLAG | GSS_C_REPLAY_FLAG | GSS_C_INTEG_FLAG;
	if (tds->connection->gssapi_use_delegation)
		gssapi_flags |= GSS_C_DELEG_FLAG;

	maj_stat = gss_init_sec_context(&min_stat, GSS_C_NO_CREDENTIAL, &auth->gss_context, auth->target_name,

					GSS_C_NULL_OID,
					gssapi_flags,
					0, NULL,
					token_ptr, NULL,
					&send_tok, &ret_flags, NULL);

	auth->last_stat = maj_stat;
	if (maj_stat != GSS_S_COMPLETE && maj_stat != GSS_S_CONTINUE_NEEDED) {
		gss_release_buffer(&min_stat, &send_tok);
		return TDS_FAIL;
	}


	auth->tds_auth.packet = (TDS_UCHAR *) send_tok.value;
	auth->tds_auth.packet_len = send_tok.length;
	return TDS_SUCCEED;
}
