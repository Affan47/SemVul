iscsi_itt_to_ctask(struct iscsi_conn *conn, itt_t itt)
{
	struct iscsi_task *task;

	if (iscsi_verify_itt(conn, itt))
		return NULL;

	task = iscsi_itt_to_task(conn, itt);
	if (!task || !task->sc)
		return NULL;

	if (task->sc->SCp.phase != conn->session->age) {
		iscsi_session_printk(KERN_ERR, conn->session,
				  "task's session age %d, expected %d\n",
				  task->sc->SCp.phase, conn->session->age);
		return NULL;
	}

	return task;
}
