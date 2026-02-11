_exkey_is_valid(slurm_cred_ctx_t ctx)
{
	if (!ctx->exkey)
		return false;

	if (time(NULL) > ctx->exkey_exp) {
		debug2("old job credential key slurmd expired");
		(*(ops.crypto_destroy_key))(ctx->exkey);
		ctx->exkey = NULL;
		return false;
	}

	return true;
}
