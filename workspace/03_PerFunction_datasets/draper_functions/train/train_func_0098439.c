recover_master(struct dlm_rsb *r, unsigned int *count)
{
	struct dlm_ls *ls = r->res_ls;
	int our_nodeid, dir_nodeid;
	int is_removed = 0;
	int error;

	if (is_master(r))
		return 0;

	is_removed = dlm_is_removed(ls, r->res_nodeid);

	if (!is_removed && !rsb_flag(r, RSB_NEW_MASTER))
		return 0;

	our_nodeid = dlm_our_nodeid();
	dir_nodeid = dlm_dir_nodeid(r);

	if (dir_nodeid == our_nodeid) {
		if (is_removed) {
			r->res_master_nodeid = our_nodeid;
			r->res_nodeid = 0;
		}


		set_new_master(r);
		error = 0;
	} else {
		recover_idr_add(r);
		error = dlm_send_rcom_lookup(r, dir_nodeid);
	}

	(*count)++;
	return error;
}
