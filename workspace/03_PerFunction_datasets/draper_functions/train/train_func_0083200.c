check_cpu_stall(struct rcu_state *rsp, struct rcu_data *rdp)
{
	unsigned long completed;
	unsigned long gpnum;
	unsigned long gps;
	unsigned long j;
	unsigned long js;
	struct rcu_node *rnp;

	if (rcu_cpu_stall_suppress || !rcu_gp_in_progress(rsp))
		return;
	j = jiffies;


	gpnum = READ_ONCE(rsp->gpnum);
	smp_rmb();
	js = READ_ONCE(rsp->jiffies_stall);
	smp_rmb();
	gps = READ_ONCE(rsp->gp_start);
	smp_rmb();
	completed = READ_ONCE(rsp->completed);
	if (ULONG_CMP_GE(completed, gpnum) ||
	    ULONG_CMP_LT(j, js) ||
	    ULONG_CMP_GE(gps, js))
		return;
	rnp = rdp->mynode;
	if (rcu_gp_in_progress(rsp) &&
	    (READ_ONCE(rnp->qsmask) & rdp->grpmask)) {


		print_cpu_stall(rsp);

	} else if (rcu_gp_in_progress(rsp) &&
		   ULONG_CMP_GE(j, js + RCU_STALL_RAT_DELAY)) {


		print_other_cpu_stall(rsp, gpnum);
	}
}
