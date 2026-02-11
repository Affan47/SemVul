_agent_thread(void *args)
{
	List ret_list = NULL;
	thd_t *thread_ptr = (thd_t *) args;
	ListIterator itr;
	ret_data_info_t *ret_data_info = NULL;
	int rc = 0, msg_rc;

	ret_list = slurm_send_recv_msgs(thread_ptr->nodelist,
					&thread_ptr->msg,
					params.timeout, false);
	if (ret_list == NULL) {
		error("slurm_send_recv_msgs: %m");
		exit(1);
	}

	itr = list_iterator_create(ret_list);
	while ((ret_data_info = list_next(itr))) {
		msg_rc = slurm_get_return_code(ret_data_info->type,
					       ret_data_info->data);
		if (msg_rc == SLURM_SUCCESS)
			continue;

		error("REQUEST_FILE_BCAST(%s): %s",
		      ret_data_info->node_name,
		      slurm_strerror(msg_rc));
		rc = MAX(rc, msg_rc);
	}

	thread_ptr->rc = rc;
	list_iterator_destroy(itr);
	if (ret_list)
		list_destroy(ret_list);
	slurm_mutex_lock(&agent_cnt_mutex);
	agent_cnt--;
	pthread_cond_broadcast(&agent_cnt_cond);
	slurm_mutex_unlock(&agent_cnt_mutex);
	return NULL;
}
