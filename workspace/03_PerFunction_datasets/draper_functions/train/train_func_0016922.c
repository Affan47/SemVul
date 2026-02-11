fcoe_ctlr_age_fcfs(struct fcoe_ctlr *fip)
{
	struct fcoe_fcf *fcf;
	struct fcoe_fcf *next;
	unsigned long next_timer = jiffies + msecs_to_jiffies(FIP_VN_KA_PERIOD);
	unsigned long deadline;
	unsigned long sel_time = 0;
	struct list_head del_list;
	struct fc_stats *stats;

	INIT_LIST_HEAD(&del_list);

	stats = per_cpu_ptr(fip->lp->stats, get_cpu());

	list_for_each_entry_safe(fcf, next, &fip->fcfs, list) {
		deadline = fcf->time + fcf->fka_period + fcf->fka_period / 2;
		if (fip->sel_fcf == fcf) {
			if (time_after(jiffies, deadline)) {
				stats->MissDiscAdvCount++;
				printk(KERN_INFO "libfcoe: host%d: "
				       "Missing Discovery Advertisement "
				       "for fab %16.16llx count %lld\n",
				       fip->lp->host->host_no, fcf->fabric_name,
				       stats->MissDiscAdvCount);
			} else if (time_after(next_timer, deadline))
				next_timer = deadline;
		}

		deadline += fcf->fka_period;
		if (time_after_eq(jiffies, deadline)) {
			if (fip->sel_fcf == fcf)
				fip->sel_fcf = NULL;


			list_del(&fcf->list);
			list_add(&fcf->list, &del_list);
			stats->VLinkFailureCount++;
		} else {
			if (time_after(next_timer, deadline))
				next_timer = deadline;
			if (fcoe_ctlr_mtu_valid(fcf) &&
			    (!sel_time || time_before(sel_time, fcf->time)))
				sel_time = fcf->time;
		}
	}
	put_cpu();

	list_for_each_entry_safe(fcf, next, &del_list, list) {

		fcoe_sysfs_fcf_del(fcf);
	}

	if (sel_time && !fip->sel_fcf && !fip->sel_time) {
		sel_time += msecs_to_jiffies(FCOE_CTLR_START_DELAY);
		fip->sel_time = sel_time;
	}

	return next_timer;
}
