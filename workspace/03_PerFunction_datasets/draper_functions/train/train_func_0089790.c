slurm_cred_ctx_pack(slurm_cred_ctx_t ctx, Buf buffer)
{
	slurm_mutex_lock(&ctx->mutex);
	_job_state_pack(ctx, buffer);
	_cred_state_pack(ctx, buffer);
	slurm_mutex_unlock(&ctx->mutex);

	return SLURM_SUCCESS;
}
