get_nonce(private_quick_mode_t *this, chunk_t *nonce,
					  message_t *message)
{
	nonce_payload_t *nonce_payload;

	nonce_payload = (nonce_payload_t*)message->get_payload(message, PLV1_NONCE);
	if (!nonce_payload)
	{
		DBG1(DBG_IKE, "NONCE payload missing in message");
		return FALSE;
	}
	*nonce = nonce_payload->get_nonce(nonce_payload);

	return TRUE;
}
