bnx2i_conn_destroy(struct iscsi_cls_conn *cls_conn)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct bnx2i_conn *bnx2i_conn = conn->dd_data;
	struct Scsi_Host *shost;
	struct bnx2i_hba *hba;
	struct bnx2i_work *work, *tmp;
	unsigned cpu = 0;
	struct bnx2i_percpu_s *p;

	shost = iscsi_session_to_shost(iscsi_conn_to_session(cls_conn));
	hba = iscsi_host_priv(shost);

	bnx2i_conn_free_login_resources(hba, bnx2i_conn);

	if (atomic_read(&bnx2i_conn->work_cnt)) {
		for_each_online_cpu(cpu) {
			p = &per_cpu(bnx2i_percpu, cpu);
			spin_lock_bh(&p->p_work_lock);
			list_for_each_entry_safe(work, tmp,
						 &p->work_list, list) {
				if (work->session == conn->session &&
				    work->bnx2i_conn == bnx2i_conn) {
					list_del_init(&work->list);
					kfree(work);
					if (!atomic_dec_and_test(
							&bnx2i_conn->work_cnt))
						break;
				}
			}
			spin_unlock_bh(&p->p_work_lock);
		}
	}

	iscsi_conn_teardown(cls_conn);
}
