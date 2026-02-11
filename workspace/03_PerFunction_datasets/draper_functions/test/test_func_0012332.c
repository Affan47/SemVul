cg_logwork_uint32(struct work *work, uint32_t nonce, bool ok)
{
	if(opt_logwork_path) {
		unsigned char nonce_bin[5] = {0};
		memcpy(nonce_bin, &nonce, 4);
		cg_logwork(work, nonce_bin, ok);
	}
}
