qed_spq_post(struct qed_hwfn *p_hwfn,
		 struct qed_spq_entry *p_ent,
		 u8 *fw_return_code)
{
	int rc = 0;
	struct qed_spq *p_spq = p_hwfn ? p_hwfn->p_spq : NULL;
	bool b_ret_ent = true;

	if (!p_hwfn)
		return -EINVAL;

	if (!p_ent) {
		DP_NOTICE(p_hwfn, "Got a NULL pointer\n");
		return -EINVAL;
	}


	rc = qed_spq_fill_entry(p_hwfn, p_ent);

	spin_lock_bh(&p_spq->lock);


	if (rc)
		goto spq_post_fail;


	rc = qed_spq_add_entry(p_hwfn, p_ent, p_ent->priority);
	if (rc)
		goto spq_post_fail;

	rc = qed_spq_pend_post(p_hwfn);
	if (rc) {


		b_ret_ent = false;
		goto spq_post_fail;
	}

	spin_unlock_bh(&p_spq->lock);

	if (p_ent->comp_mode == QED_SPQ_MODE_EBLOCK) {


		rc = qed_spq_block(p_hwfn, p_ent, fw_return_code);
		if (rc)
			goto spq_post_fail2;


		qed_spq_return_entry(p_hwfn, p_ent);
	}
	return rc;

spq_post_fail2:
	spin_lock_bh(&p_spq->lock);
	list_del(&p_ent->list);
	qed_chain_return_produced(&p_spq->chain);

spq_post_fail:

	if (b_ret_ent)
		__qed_spq_return_entry(p_hwfn, p_ent);
	spin_unlock_bh(&p_spq->lock);

	return rc;
}
