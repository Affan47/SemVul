cxgbi_sock_rcv_peer_close(struct cxgbi_sock *csk)
{
	log_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%lx,%u.\n",
		csk, (csk)->state, (csk)->flags, (csk)->tid);
	cxgbi_sock_get(csk);
	spin_lock_bh(&csk->lock);

	if (cxgbi_sock_flag(csk, CTPF_ABORT_RPL_PENDING))
		goto done;

	switch (csk->state) {
	case CTP_ESTABLISHED:
		cxgbi_sock_set_state(csk, CTP_PASSIVE_CLOSE);
		break;
	case CTP_ACTIVE_CLOSE:
		cxgbi_sock_set_state(csk, CTP_CLOSE_WAIT_2);
		break;
	case CTP_CLOSE_WAIT_1:
		cxgbi_sock_closed(csk);
		break;
	case CTP_ABORTING:
		break;
	default:
		pr_err("csk 0x%p,%u,0x%lx,%u, bad state.\n",
			csk, csk->state, csk->flags, csk->tid);
	}
	cxgbi_inform_iscsi_conn_closing(csk);
done:
	spin_unlock_bh(&csk->lock);
	cxgbi_sock_put(csk);
}
