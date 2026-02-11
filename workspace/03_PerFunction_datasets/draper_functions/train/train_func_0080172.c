rcu_report_exp_cpu_mult(struct rcu_state *rsp, struct rcu_node *rnp,
				    unsigned long mask, bool wake)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&rnp->lock, flags);
	smp_mb__after_unlock_lock();
	if (!(rnp->expmask & mask)) {
		raw_spin_unlock_irqrestore(&rnp->lock, flags);
		return;
	}
	rnp->expmask &= ~mask;
	__rcu_report_exp_rnp(rsp, rnp, wake, flags);
}
