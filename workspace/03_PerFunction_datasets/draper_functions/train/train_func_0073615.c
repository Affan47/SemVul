receive_remove(struct dlm_ls *ls, struct dlm_message *ms)
{
	char name[DLM_RESNAME_MAXLEN+1];
	struct dlm_rsb *r;
	uint32_t hash, b;
	int rv, len, dir_nodeid, from_nodeid;

	from_nodeid = ms->m_header.h_nodeid;

	len = receive_extralen(ms);

	if (len > DLM_RESNAME_MAXLEN) {
		log_error(ls, "receive_remove from %d bad len %d",
			  from_nodeid, len);
		return;
	}

	dir_nodeid = dlm_hash2nodeid(ls, ms->m_hash);
	if (dir_nodeid != dlm_our_nodeid()) {
		log_error(ls, "receive_remove from %d bad nodeid %d",
			  from_nodeid, dir_nodeid);
		return;
	}


	memset(name, 0, sizeof(name));
	memcpy(name, ms->m_extra, len);

	hash = jhash(name, len, 0);
	b = hash & (ls->ls_rsbtbl_size - 1);

	spin_lock(&ls->ls_rsbtbl[b].lock);

	rv = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].toss, name, len, &r);
	if (rv) {

		rv = dlm_search_rsb_tree(&ls->ls_rsbtbl[b].keep, name, len, &r);
		if (rv) {

			log_error(ls, "receive_remove from %d not found %s",
				  from_nodeid, name);
			spin_unlock(&ls->ls_rsbtbl[b].lock);
			return;
		}
		if (r->res_master_nodeid != from_nodeid) {

			log_error(ls, "receive_remove keep from %d master %d",
				  from_nodeid, r->res_master_nodeid);
			dlm_print_rsb(r);
			spin_unlock(&ls->ls_rsbtbl[b].lock);
			return;
		}

		log_debug(ls, "receive_remove from %d master %d first %x %s",
			  from_nodeid, r->res_master_nodeid, r->res_first_lkid,
			  name);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		return;
	}

	if (r->res_master_nodeid != from_nodeid) {
		log_error(ls, "receive_remove toss from %d master %d",
			  from_nodeid, r->res_master_nodeid);
		dlm_print_rsb(r);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		return;
	}

	if (kref_put(&r->res_ref, kill_rsb)) {
		rb_erase(&r->res_hashnode, &ls->ls_rsbtbl[b].toss);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
		dlm_free_rsb(r);
	} else {
		log_error(ls, "receive_remove from %d rsb ref error",
			  from_nodeid);
		dlm_print_rsb(r);
		spin_unlock(&ls->ls_rsbtbl[b].lock);
	}
}
