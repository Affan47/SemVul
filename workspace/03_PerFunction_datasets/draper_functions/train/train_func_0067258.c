crypto_authenc_esn_genicv(struct aead_request *req,
				     unsigned int flags)
{
	struct crypto_aead *authenc_esn = crypto_aead_reqtfm(req);
	struct authenc_esn_request_ctx *areq_ctx = aead_request_ctx(req);
	struct crypto_authenc_esn_ctx *ctx = crypto_aead_ctx(authenc_esn);
	struct crypto_ahash *auth = ctx->auth;
	u8 *hash = PTR_ALIGN((u8 *)areq_ctx->tail,
			     crypto_ahash_alignmask(auth) + 1);
	struct ahash_request *ahreq = (void *)(areq_ctx->tail + ctx->reqoff);
	unsigned int authsize = crypto_aead_authsize(authenc_esn);
	unsigned int assoclen = req->assoclen;
	unsigned int cryptlen = req->cryptlen;
	struct scatterlist *dst = req->dst;
	u32 tmp[2];

	if (!authsize)
		return 0;


	scatterwalk_map_and_copy(tmp, dst, 0, 8, 0);
	scatterwalk_map_and_copy(tmp, dst, 4, 4, 1);
	scatterwalk_map_and_copy(tmp + 1, dst, assoclen + cryptlen, 4, 1);

	sg_init_table(areq_ctx->dst, 2);
	dst = scatterwalk_ffwd(areq_ctx->dst, dst, 4);

	ahash_request_set_tfm(ahreq, auth);
	ahash_request_set_crypt(ahreq, dst, hash, assoclen + cryptlen);
	ahash_request_set_callback(ahreq, flags,
				   authenc_esn_geniv_ahash_done, req);

	return crypto_ahash_digest(ahreq) ?:
	       crypto_authenc_esn_genicv_tail(req, aead_request_flags(req));
}
