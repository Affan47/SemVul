checkpoint_tasks (uint32_t job_id, uint32_t step_id,
			     time_t begin_time, char *image_dir,
			     uint16_t wait, char *nodelist)
{
	int rc = SLURM_SUCCESS, temp_rc;
	checkpoint_tasks_msg_t ckpt_req;
	slurm_msg_t req_msg;
	List ret_list;
        ret_data_info_t *ret_data_info = NULL;

	slurm_msg_t_init(&req_msg);
	ckpt_req.job_id		= job_id;
	ckpt_req.job_step_id 	= step_id;
	ckpt_req.timestamp	= begin_time;
	ckpt_req.image_dir	= image_dir;
	req_msg.msg_type	= REQUEST_CHECKPOINT_TASKS;
	req_msg.data		= &ckpt_req;

	if ((ret_list = slurm_send_recv_msgs(nodelist, &req_msg, (wait*1000),
					     false))) {
		while ((ret_data_info = list_pop(ret_list))) {
                        temp_rc = slurm_get_return_code(ret_data_info->type,
                                                        ret_data_info->data);
                        if (temp_rc)
                                rc = temp_rc;
                }
	} else {
                error("slurm_checkpoint_tasks: no list was returned");
                rc = SLURM_ERROR;
	}
	slurm_seterrno(rc);
	return rc;
}
