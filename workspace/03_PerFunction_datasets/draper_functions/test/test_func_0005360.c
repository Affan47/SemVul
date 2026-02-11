rcu_adopt_orphan_cbs(struct rcu_state *rsp, unsigned long flags)
{
	int i;
	struct rcu_data *rdp = raw_cpu_ptr(rsp->rda);


	if (!IS_ENABLED(CONFIG_HOTPLUG_CPU) ||
	    rcu_nocb_adopt_orphan_cbs(rsp, rdp, flags))
		return;


	rdp->qlen_lazy += rsp->qlen_lazy;
	rdp->qlen += rsp->qlen;
	rdp->n_cbs_adopted += rsp->qlen;
	if (rsp->qlen_lazy != rsp->qlen)
		rcu_idle_count_callbacks_posted();
	rsp->qlen_lazy = 0;
	rsp->qlen = 0;


	if (rsp->orphan_donelist != NULL) {
		*rsp->orphan_donetail = *rdp->nxttail[RCU_DONE_TAIL];
		*rdp->nxttail[RCU_DONE_TAIL] = rsp->orphan_donelist;
		for (i = RCU_NEXT_SIZE - 1; i >= RCU_DONE_TAIL; i--)
			if (rdp->nxttail[i] == rdp->nxttail[RCU_DONE_TAIL])
				rdp->nxttail[i] = rsp->orphan_donetail;
		rsp->orphan_donelist = NULL;
		rsp->orphan_donetail = &rsp->orphan_donelist;
	}


	if (rsp->orphan_nxtlist != NULL) {
		*rdp->nxttail[RCU_NEXT_TAIL] = rsp->orphan_nxtlist;
		rdp->nxttail[RCU_NEXT_TAIL] = rsp->orphan_nxttail;
		rsp->orphan_nxtlist = NULL;
		rsp->orphan_nxttail = &rsp->orphan_nxtlist;
	}
}
