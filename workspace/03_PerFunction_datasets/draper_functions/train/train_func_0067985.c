cxgbi_sock_check_wr_invariants(const struct cxgbi_sock *csk)
{
	int pending = cxgbi_sock_count_pending_wrs(csk);

	if (unlikely(csk->wr_cred + pending != csk->wr_max_cred))
		pr_err("csk 0x%p, tid %u, credit %u + %u != %u.\n",
			csk, csk->tid, csk->wr_cred, pending, csk->wr_max_cred);
}
