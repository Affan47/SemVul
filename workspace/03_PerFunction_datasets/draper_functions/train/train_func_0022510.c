slurm_cred_pack(slurm_cred_t *cred, Buf buffer)
{
	xassert(cred != NULL);
	xassert(cred->magic == CRED_MAGIC);

	slurm_mutex_lock(&cred->mutex);

	_pack_cred(cred, buffer);
	xassert(cred->siglen > 0);
	packmem(cred->signature, cred->siglen, buffer);

	slurm_mutex_unlock(&cred->mutex);

	return;
}
