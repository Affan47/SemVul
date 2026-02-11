_rpc_health_check(slurm_msg_t *msg)
{
	int        rc = SLURM_SUCCESS;
	uid_t req_uid = g_slurm_auth_get_uid(msg->auth_cred, NULL);

	if (!_slurm_authorized_user(req_uid)) {
		error("Security violation, health check RPC from uid %d",
		      req_uid);
		rc = ESLURM_USER_ID_MISSING;
	}


	if (slurm_send_rc_msg(msg, rc) < 0) {
		error("Error responding to ping: %m");
		send_registration_msg(SLURM_SUCCESS, false);
	}

	if ((rc == SLURM_SUCCESS) && (conf->health_check_program)) {
		char *env[1] = { NULL };
		rc = run_script("health_check", conf->health_check_program,
				0, 60, env, 0);
	}


	_enforce_job_mem_limit();
	return rc;
}
