slurm_auth_destroy( slurm_auth_credential_t *cred )
{
	if ( cred == NULL ) {
		plugin_errno = SLURM_AUTH_MEMORY;
		return SLURM_ERROR;
	}
	xfree( cred );
	return SLURM_SUCCESS;
}
