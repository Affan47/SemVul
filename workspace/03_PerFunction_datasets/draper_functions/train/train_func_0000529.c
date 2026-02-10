challenge_cb(struct fp_img_dev *dev, int status,
	uint16_t num_regs, unsigned char *data, void *user_data)
{
	struct fpi_ssm *ssm = user_data;
	struct uru4k_dev *urudev = dev->priv;
	unsigned char *respdata;
	PK11Context *ctx;
	int r, outlen;

	r = status;
	if (status != 0) {
		fpi_ssm_mark_aborted(ssm, status);
		return;
	}


	respdata = g_malloc(CR_LENGTH);
	ctx = PK11_CreateContextBySymKey(urudev->cipher, CKA_ENCRYPT,
					 urudev->symkey, urudev->param);
	if (PK11_CipherOp(ctx, respdata, &outlen, CR_LENGTH, data, CR_LENGTH) != SECSuccess
	    || PK11_Finalize(ctx) != SECSuccess) {
		fp_err("Failed to encrypt challenge data");
		r = -ECONNABORTED;
		g_free(respdata);
	}
	PK11_DestroyContext(ctx, PR_TRUE);

	if (r >= 0) {
		r = write_regs(dev, REG_RESPONSE, CR_LENGTH, respdata, response_cb, ssm);
		g_free(respdata);
	}
	if (r < 0)
		fpi_ssm_mark_aborted(ssm, r);
}
