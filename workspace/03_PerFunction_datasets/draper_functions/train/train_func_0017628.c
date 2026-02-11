credssp_send(rdpCredssp* credssp, BLOB* negoToken, BLOB* authInfo, BLOB* pubKeyAuth)
{
	STREAM* s;
	int length;
	int ts_request_length;
	int nego_tokens_length;
	int pub_key_auth_length;
	int auth_info_length;

	nego_tokens_length = (negoToken != NULL) ? credssp_skip_nego_tokens(negoToken->length) : 0;
	pub_key_auth_length = (pubKeyAuth != NULL) ? credssp_skip_pub_key_auth(pubKeyAuth->length) : 0;
	auth_info_length = (authInfo != NULL) ? credssp_skip_auth_info(authInfo->length) : 0;

	length = nego_tokens_length + pub_key_auth_length + auth_info_length;
	ts_request_length = credssp_skip_ts_request(length);

	s = stream_new(ts_request_length);


	length = ber_get_content_length(ts_request_length);
	ber_write_sequence_tag(s, length);
	ber_write_contextual_tag(s, 0, 3, True);
	ber_write_integer(s, 2);


	if (nego_tokens_length > 0)
	{
		length = ber_get_content_length(nego_tokens_length);
		length -= ber_write_contextual_tag(s, 1, length, True);
		length -= ber_write_sequence_tag(s, length);
		length -= ber_write_sequence_tag(s, length);
		length -= ber_write_contextual_tag(s, 0, length, True);
		ber_write_octet_string(s, negoToken->data, length);
	}


	if (auth_info_length > 0)
	{
		length = ber_get_content_length(auth_info_length);
		length -= ber_write_contextual_tag(s, 2, length, True);
		ber_write_octet_string(s, authInfo->data, authInfo->length);
	}


	if (pub_key_auth_length > 0)
	{
		length = ber_get_content_length(pub_key_auth_length);
		length -= ber_write_contextual_tag(s, 3, length, True);
		ber_write_octet_string(s, pubKeyAuth->data, length);
	}

	transport_write(credssp->transport, s);
}
