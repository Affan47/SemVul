credssp_authenticate(rdpCredssp* credssp)
{
	NTLMSSP *ntlmssp = credssp->ntlmssp;
	STREAM* s = stream_new(0);
	uint8* negoTokenBuffer = (uint8*) xmalloc(2048);

	credssp_ntlmssp_init(credssp);

	if (credssp_get_public_key(credssp) == 0)
		return 0;


	s->p = s->data = negoTokenBuffer;
	ntlmssp_send(ntlmssp, s);
	credssp->negoToken.data = s->data;
	credssp->negoToken.length = s->p - s->data;
	credssp_send(credssp, &credssp->negoToken, NULL, NULL);


	if (credssp_recv(credssp, &credssp->negoToken, NULL, NULL) < 0)
		return -1;

	s->p = s->data = credssp->negoToken.data;
	ntlmssp_recv(ntlmssp, s);

	freerdp_blob_free(&credssp->negoToken);


	s->p = s->data = negoTokenBuffer;
	ntlmssp_send(ntlmssp, s);


	credssp->negoToken.data = s->data;
	credssp->negoToken.length = s->p - s->data;
	credssp_encrypt_public_key(credssp, &credssp->pubKeyAuth);
	credssp_send(credssp, &credssp->negoToken, NULL, &credssp->pubKeyAuth);


	if (credssp_recv(credssp, &credssp->negoToken, NULL, &credssp->pubKeyAuth) < 0)
		return -1;

	if (credssp_verify_public_key(credssp, &credssp->pubKeyAuth) == 0)
	{

		return 0;
	}

	freerdp_blob_free(&credssp->negoToken);
	freerdp_blob_free(&credssp->pubKeyAuth);


	credssp_encode_ts_credentials(credssp);
	credssp_encrypt_ts_credentials(credssp, &credssp->authInfo);
	credssp_send(credssp, NULL, &credssp->authInfo, NULL);

	xfree(s);

	return 1;
}
