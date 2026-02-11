_handle_get_my_kvsname(int fd, int lrank, client_req_t *req)
{
	client_resp_t *resp;
	int rc = 0;

	debug3("mpi/pmi2: in _handle_get_my_kvsname");
	resp = client_resp_new();
	client_resp_append(resp, CMD_KEY"="GETMYKVSNAMERESP_CMD" "
			   RC_KEY"=%d " KVSNAME_KEY"=%u.%u\n",
			   rc, job_info.jobid, job_info.stepid);
	rc = client_resp_send(resp, fd);
	client_resp_free(resp);
	debug3("mpi/pmi2: out _handle_get_my_kvsname");
	return rc;
}
