gcm_decrypt_done(struct crypto_async_request *areq, int err)
{
	struct aead_request *req = areq->data;

	if (!err)
		err = crypto_gcm_verify(req);

	aead_request_complete(req, err);
}
