crypt_iv_tcw_gen(struct crypt_config *cc, u8 *iv,
			    struct dm_crypt_request *dmreq)
{
	struct iv_tcw_private *tcw = &cc->iv_gen_private.tcw;
	u64 sector = cpu_to_le64((u64)dmreq->iv_sector);
	u8 *src;
	int r = 0;


	if (bio_data_dir(dmreq->ctx->bio_in) != WRITE) {
		src = kmap_atomic(sg_page(&dmreq->sg_in));
		r = crypt_iv_tcw_whitening(cc, dmreq, src + dmreq->sg_in.offset);
		kunmap_atomic(src);
	}


	memcpy(iv, tcw->iv_seed, cc->iv_size);
	crypto_xor(iv, (u8 *)&sector, 8);
	if (cc->iv_size > 8)
		crypto_xor(&iv[8], (u8 *)&sector, cc->iv_size - 8);

	return r;
}
