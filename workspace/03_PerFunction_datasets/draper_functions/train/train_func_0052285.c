crypto_authenc_decrypt_tail(struct aead_request *req,
				       unsigned int flags)
{
	struct crypto_aead *authenc = crypto_aead_reqtfm(req);
	struct aead_instance *inst = aead_alg_instance(authenc);
	struct crypto_authenc_ctx *ctx = crypto_aead_ctx(authenc);
	struct authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	struct authenc_request_ctx *areq_ctx = aead_request_ctx(req);
	struct ahash_request *ahreq = (void *)(areq_ctx->tail + ictx->reqoff);
	struct ablkcipher_request *abreq = (void *)(areq_ctx->tail +
						    ictx->reqoff);
	unsigned int authsize = crypto_aead_authsize(authenc);
	u8 *ihash = ahreq->result + authsize;
	struct scatterlist *src, *dst;

	scatterwalk_map_and_copy(ihash, req->src, ahreq->nbytes, authsize, 0);

	if (crypto_memneq(ihash, ahreq->result, authsize))
		return -EBADMSG;

	sg_init_table(areq_ctx->src, 2);
	src = scatterwalk_ffwd(areq_ctx->src, req->src, req->assoclen);
	dst = src;

	if (req->src != req->dst) {
		sg_init_table(areq_ctx->dst, 2);
		dst = scatterwalk_ffwd(areq_ctx->dst, req->dst, req->assoclen);
	}

	ablkcipher_request_set_tfm(abreq, ctx->enc);
	ablkcipher_request_set_callback(abreq, aead_request_flags(req),
					req->base.complete, req->base.data);
	ablkcipher_request_set_crypt(abreq, src, dst,
				     req->cryptlen - authsize, req->iv);

	return crypto_ablkcipher_decrypt(abreq);
}
