dlm_recover_master_reply(struct dlm_ls *ls, struct dlm_rcom *rc)
{
	struct dlm_rsb *r;
	int ret_nodeid, new_master;

	r = recover_idr_find(ls, rc->rc_id);
	if (!r) {
		log_error(ls, "dlm_recover_master_reply no id %llx",
			  (unsigned long long)rc->rc_id);
		goto out;
	}

	ret_nodeid = rc->rc_result;

	if (ret_nodeid == dlm_our_nodeid())
		new_master = 0;
	else
		new_master = ret_nodeid;

	lock_rsb(r);
	r->res_master_nodeid = ret_nodeid;
	r->res_nodeid = new_master;
	set_new_master(r);
	unlock_rsb(r);
	recover_idr_del(r);

	if (recover_idr_empty(ls))
		wake_up(&ls->ls_wait_general);
 out:
	return 0;
}
