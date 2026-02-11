slurmdbd_pack_init_msg(dbd_init_msg_t *msg, uint16_t rpc_version,
		       Buf buffer, char *auth_info)
{
	int rc;
	void *auth_cred;

	pack16(msg->rollback, buffer);
	pack16(msg->version, buffer);


	if (rpc_version >= SLURMDBD_2_5_VERSION) {
		packstr(msg->cluster_name, buffer);
	}

	auth_cred = g_slurm_auth_create(NULL, 2, auth_info);
	if (auth_cred == NULL) {
		error("Creating authentication credential: %s",
		      g_slurm_auth_errstr(g_slurm_auth_errno(NULL)));
		errno = ESLURM_ACCESS_DENIED;
	} else {
		rc = g_slurm_auth_pack(auth_cred, buffer);
		if (rc) {
			error("Packing authentication credential: %s",
			      g_slurm_auth_errstr(
				      g_slurm_auth_errno(auth_cred)));
			errno = g_slurm_auth_errno(auth_cred);
		}
		(void) g_slurm_auth_destroy(auth_cred);
	}
}
