__receive_convert_reply(struct dlm_rsb *r, struct dlm_lkb *lkb,
				    struct dlm_message *ms)
{

	switch (ms->m_result) {
	case -EAGAIN:

		queue_cast(r, lkb, -EAGAIN);
		break;

	case -EDEADLK:
		receive_flags_reply(lkb, ms);
		revert_lock_pc(r, lkb);
		queue_cast(r, lkb, -EDEADLK);
		break;

	case -EINPROGRESS:

		receive_flags_reply(lkb, ms);
		if (is_demoted(lkb))
			munge_demoted(lkb);
		del_lkb(r, lkb);
		add_lkb(r, lkb, DLM_LKSTS_CONVERT);
		add_timeout(lkb);
		break;

	case 0:

		receive_flags_reply(lkb, ms);
		if (is_demoted(lkb))
			munge_demoted(lkb);
		grant_lock_pc(r, lkb, ms);
		queue_cast(r, lkb, 0);
		break;

	default:
		log_error(r->res_ls, "receive_convert_reply %x remote %d %x %d",
			  lkb->lkb_id, ms->m_header.h_nodeid, ms->m_lkid,
			  ms->m_result);
		dlm_print_rsb(r);
		dlm_print_lkb(lkb);
	}
}
