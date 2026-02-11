iscsi_tcp_get_curr_r2t(struct iscsi_task *task)
{
	struct iscsi_session *session = task->conn->session;
	struct iscsi_tcp_task *tcp_task = task->dd_data;
	struct iscsi_r2t_info *r2t = NULL;

	if (iscsi_task_has_unsol_data(task))
		r2t = &task->unsol_r2t;
	else {
		spin_lock_bh(&session->lock);
		if (tcp_task->r2t) {
			r2t = tcp_task->r2t;

			if (r2t->data_length <= r2t->sent) {
				ISCSI_DBG_TCP(task->conn,
					      "  done with r2t %p\n", r2t);
				kfifo_in(&tcp_task->r2tpool.queue,
					    (void *)&tcp_task->r2t,
					    sizeof(void *));
				tcp_task->r2t = r2t = NULL;
			}
		}

		if (r2t == NULL) {
			if (kfifo_out(&tcp_task->r2tqueue,
			    (void *)&tcp_task->r2t, sizeof(void *)) !=
			    sizeof(void *))
				r2t = NULL;
			else
				r2t = tcp_task->r2t;
		}
		spin_unlock_bh(&session->lock);
	}

	return r2t;
}
