bfa_tskim_free(struct bfa_tskim_s *tskim)
{
	WARN_ON(!bfa_q_is_on_q_func(&tskim->itnim->tsk_q, &tskim->qe));
	list_del(&tskim->qe);
	list_add_tail(&tskim->qe, &tskim->fcpim->tskim_free_q);
}
