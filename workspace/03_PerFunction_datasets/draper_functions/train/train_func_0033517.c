force_qs_rnp(struct rcu_state *rsp,
			 int (*f)(struct rcu_data *rsp, bool *isidle,
				  unsigned long *maxj),
			 bool *isidle, unsigned long *maxj)
{
	unsigned long bit;
	int cpu;
	unsigned long flags;
	unsigned long mask;
	struct rcu_node *rnp;

	rcu_for_each_leaf_node(rsp, rnp) {
		cond_resched_rcu_qs();
		mask = 0;
		raw_spin_lock_irqsave(&rnp->lock, flags);
		smp_mb__after_unlock_lock();
		if (rnp->qsmask == 0) {
			if (rcu_state_p == &rcu_sched_state ||
			    rsp != rcu_state_p ||
			    rcu_preempt_blocked_readers_cgp(rnp)) {


				rcu_initiate_boost(rnp, flags);

				continue;
			}
			if (rnp->parent &&
			    (rnp->parent->qsmask & rnp->grpmask)) {


				rcu_report_unblock_qs_rnp(rsp, rnp, flags);

				continue;
			}
		}
		cpu = rnp->grplo;
		bit = 1;
		for (; cpu <= rnp->grphi; cpu++, bit <<= 1) {
			if ((rnp->qsmask & bit) != 0) {
				if (f(per_cpu_ptr(rsp->rda, cpu), isidle, maxj))
					mask |= bit;
			}
		}
		if (mask != 0) {

			rcu_report_qs_rnp(mask, rsp, rnp, rnp->gpnum, flags);
		} else {

			raw_spin_unlock_irqrestore(&rnp->lock, flags);
		}
	}
}
