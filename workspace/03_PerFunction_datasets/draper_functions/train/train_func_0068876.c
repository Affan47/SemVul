dlm_set_reco_dead_node(struct dlm_ctxt *dlm,
					  u8 dead_node)
{
	assert_spin_locked(&dlm->spinlock);
	if (dlm->reco.dead_node != dead_node)
		mlog(0, "%s: changing dead_node from %u to %u\n",
		     dlm->name, dlm->reco.dead_node, dead_node);
	dlm->reco.dead_node = dead_node;
}
