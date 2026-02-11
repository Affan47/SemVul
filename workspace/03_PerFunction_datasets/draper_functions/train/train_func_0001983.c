_slurm_cred_sign(slurm_cred_ctx_t ctx, slurm_cred_t *cred)
{
	Buf           buffer;
	int           rc;

	buffer = init_buf(4096);
	_pack_cred(cred, buffer);
	rc = (*(ops.crypto_sign))(ctx->key,
				  get_buf_data(buffer),
				  get_buf_offset(buffer),
				  &cred->signature,
				  &cred->siglen);
	free_buf(buffer);

	if (rc) {
		error("Credential sign: %s",
		      (*(ops.crypto_str_error))(rc));
		return SLURM_ERROR;
	}
	return SLURM_SUCCESS;
}
