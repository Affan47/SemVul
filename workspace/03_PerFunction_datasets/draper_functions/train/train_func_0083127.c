credssp_verify_public_key(rdpCredssp* credssp, BLOB* d)
{
	uint8 *p1, *p2;
	uint8 *signature;
	BLOB public_key;
	BLOB encrypted_public_key;

	signature = d->data;
	encrypted_public_key.data = (void*) (signature + 16);
	encrypted_public_key.length = d->length - 16;

	ntlmssp_decrypt_message(credssp->ntlmssp, &encrypted_public_key, &public_key, signature);

	p1 = (uint8*) credssp->public_key.data;
	p2 = (uint8*) public_key.data;

	p2[0]--;

	if (memcmp(p1, p2, public_key.length) != 0)
	{
		printf("Could not verify server's public key echo\n");
		return 0;
	}

	p2[0]++;
	freerdp_blob_free(&public_key);
	return 1;
}
