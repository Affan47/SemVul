write_dquots(dict_t *dict, struct quota_handle *qh)
{
	dnode_t		*n;
	struct dquot	*dq;

	for (n = dict_first(dict); n; n = dict_next(dict, n)) {
		dq = dnode_get(n);
		if (dq) {
			print_dquot("write", dq);
			dq->dq_h = qh;
			update_grace_times(dq);
			qh->qh_ops->commit_dquot(dq);
		}
	}
}
