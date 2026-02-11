worker_cleanup(void *arg)
{
	CONN_Ptr conn = (CONN_Ptr) arg;
	ISTGT_LU_Ptr lu;
	int rc;

	ISTGT_TRACELOG(ISTGT_TRACE_DEBUG, "worker_cleanup\n");
	ISTGT_WARNLOG("force cleanup execute\n");


	pthread_mutex_unlock(&conn->task_queue_mutex);
	pthread_mutex_unlock(&conn->result_queue_mutex);
	if (conn->sess != NULL) {
		if (conn->sess->lu != NULL) {
			pthread_mutex_unlock(&conn->sess->lu->mutex);
		}
		pthread_mutex_unlock(&conn->sess->mutex);
	}
	if (conn->exec_lu_task != NULL) {
		conn->exec_lu_task->error = 1;
		pthread_cond_broadcast(&conn->exec_lu_task->trans_cond);
		pthread_mutex_unlock(&conn->exec_lu_task->trans_mutex);
	}
	pthread_mutex_unlock(&conn->wpdu_mutex);
	pthread_mutex_unlock(&conn->r2t_mutex);
	pthread_mutex_unlock(&conn->istgt->mutex);
	pthread_mutex_unlock(&g_conns_mutex);
	pthread_mutex_unlock(&g_last_tsih_mutex);

	conn->state = CONN_STATE_EXITING;
	if (conn->sess != NULL) {
		SESS_MTX_LOCK(conn);
		lu = conn->sess->lu;
		if (lu != NULL && lu->queue_depth != 0) {
			rc = istgt_lu_clear_task_IT(conn, lu);
			if (rc < 0) {
				ISTGT_ERRLOG("lu_clear_task_IT() failed\n");
			}
			istgt_clear_all_transfer_task(conn);
		}
		SESS_MTX_UNLOCK(conn);
	}
	if (conn->pdu.copy_pdu == 0) {
		xfree(conn->pdu.ahs);
		conn->pdu.ahs = NULL;
		if (conn->pdu.data != conn->pdu.shortdata) {
			xfree(conn->pdu.data);
		}
		conn->pdu.data = NULL;
	}
	wait_all_task(conn);
	if (conn->use_sender) {
		pthread_cond_broadcast(&conn->result_queue_cond);
		pthread_join(conn->sender_thread, NULL);
	}
	close(conn->sock);
#ifdef ISTGT_USE_KQUEUE
	close(conn->kq);
	conn->kq = -1;
#endif
	sleep(1);


	ISTGT_TRACELOG(ISTGT_TRACE_DEBUG, "cancel cleanup LOCK\n");
	MTX_LOCK(&g_conns_mutex);
	g_conns[conn->id] = NULL;
	istgt_remove_conn(conn);
	MTX_UNLOCK(&g_conns_mutex);
	ISTGT_TRACELOG(ISTGT_TRACE_DEBUG, "cancel cleanup UNLOCK\n");

	return;
}
