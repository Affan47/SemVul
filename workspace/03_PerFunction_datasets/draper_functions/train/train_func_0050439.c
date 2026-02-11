qat_alg_aead_enc(struct aead_request *areq)
{
	struct crypto_aead *aead_tfm = crypto_aead_reqtfm(areq);
	struct crypto_tfm *tfm = crypto_aead_tfm(aead_tfm);
	struct qat_alg_aead_ctx *ctx = crypto_tfm_ctx(tfm);
	struct qat_crypto_request *qat_req = aead_request_ctx(areq);
	struct icp_qat_fw_la_cipher_req_params *cipher_param;
	struct icp_qat_fw_la_auth_req_params *auth_param;
	struct icp_qat_fw_la_bulk_req *msg;
	uint8_t *iv = areq->iv;
	int ret, ctr = 0;

	ret = qat_alg_sgl_to_bufl(ctx->inst, areq->src, areq->dst, qat_req);
	if (unlikely(ret))
		return ret;

	msg = &qat_req->req;
	*msg = ctx->enc_fw_req;
	qat_req->aead_ctx = ctx;
	qat_req->aead_req = areq;
	qat_req->cb = qat_aead_alg_callback;
	qat_req->req.comn_mid.opaque_data = (uint64_t)(__force long)qat_req;
	qat_req->req.comn_mid.src_data_addr = qat_req->buf.blp;
	qat_req->req.comn_mid.dest_data_addr = qat_req->buf.bloutp;
	cipher_param = (void *)&qat_req->req.serv_specif_rqpars;
	auth_param = (void *)((uint8_t *)cipher_param + sizeof(*cipher_param));

	memcpy(cipher_param->u.cipher_IV_array, iv, AES_BLOCK_SIZE);
	cipher_param->cipher_length = areq->cryptlen;
	cipher_param->cipher_offset = areq->assoclen;

	auth_param->auth_off = 0;
	auth_param->auth_len = areq->assoclen + areq->cryptlen;

	do {
		ret = adf_send_message(ctx->inst->sym_tx, (uint32_t *)msg);
	} while (ret == -EAGAIN && ctr++ < 10);

	if (ret == -EAGAIN) {
		qat_alg_free_bufl(ctx->inst, qat_req);
		return -EBUSY;
	}
	return -EINPROGRESS;
}
