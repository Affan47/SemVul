rcu_cleanup_dead_rnp(struct rcu_node *rnp_leaf)
{
	long mask;
	struct rcu_node *rnp = rnp_leaf;

	if (!IS_ENABLED(CONFIG_HOTPLUG_CPU) ||
	    rnp->qsmaskinit || rcu_preempt_has_tasks(rnp))
		return;
	for (;;) {
		mask = rnp->grpmask;
		rnp = rnp->parent;
		if (!rnp)
			break;
		raw_spin_lock(&rnp->lock);
		smp_mb__after_unlock_lock();
		rnp->qsmaskinit &= ~mask;
		rnp->qsmask &= ~mask;
		if (rnp->qsmaskinit) {
			raw_spin_unlock(&rnp->lock);
			return;
		}
		raw_spin_unlock(&rnp->lock);
	}
}
