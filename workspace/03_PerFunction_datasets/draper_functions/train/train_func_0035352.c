_handle_abort(int fd, int lrank, client_req_t *req)
{
	int rc = SLURM_SUCCESS;
	bool is_world = false;

	debug3("mpi/pmi2: in _handle_abort");
	client_req_parse_body(req);
	client_req_get_bool(req, ISWORLD_KEY, &is_world);

	if (is_world) {
		slurm_kill_job_step(job_info.jobid, job_info.stepid, SIGKILL);
	}
	return rc;
}
