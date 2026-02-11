qed_spq_pend_post(struct qed_hwfn *p_hwfn)
{
	struct qed_spq *p_spq = p_hwfn->p_spq;
	struct qed_spq_entry *p_ent = NULL;

	while (!list_empty(&p_spq->free_pool)) {
		if (list_empty(&p_spq->unlimited_pending))
			break;

		p_ent = list_first_entry(&p_spq->unlimited_pending,
					 struct qed_spq_entry,
					 list);
		if (!p_ent)
			return -EINVAL;

		list_del(&p_ent->list);

		qed_spq_add_entry(p_hwfn, p_ent, p_ent->priority);
	}

	return qed_spq_post_list(p_hwfn, &p_spq->pending,
				 SPQ_HIGH_PRI_RESERVE_DEFAULT);
}
