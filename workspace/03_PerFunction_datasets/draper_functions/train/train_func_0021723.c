slurm_send_recv_controller_rc_msg(slurm_msg_t *req, int *rc)
{
	int ret_c;
	slurm_msg_t resp;

	if (!slurm_send_recv_controller_msg(req, &resp)) {
		*rc = slurm_get_return_code(resp.msg_type, resp.data);
		slurm_free_msg_data(resp.msg_type, resp.data);
		ret_c = 0;
	} else {
		ret_c = -1;
	}

	return ret_c;
}
