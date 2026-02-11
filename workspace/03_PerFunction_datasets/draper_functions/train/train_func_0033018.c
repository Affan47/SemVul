reclaimer(void *ptr)
{
	struct nlm_host	  *host = (struct nlm_host *) ptr;
	struct nlm_wait	  *block;
	struct nlm_rqst   *req;
	struct file_lock *fl, *next;
	u32 nsmstate;
	struct net *net = host->net;

	req = kmalloc(sizeof(*req), GFP_KERNEL);
	if (!req) {
		printk(KERN_ERR "lockd: reclaimer unable to alloc memory."
				" Locks for %s won't be reclaimed!\n",
				host->h_name);
		return 0;
	}

	allow_signal(SIGKILL);

	down_write(&host->h_rwsem);
	lockd_up(net);

	dprintk("lockd: reclaiming locks for host %s\n", host->h_name);

restart:
	nsmstate = host->h_nsmstate;


	host->h_nextrebind = jiffies;
	nlm_rebind_host(host);


	list_splice_init(&host->h_granted, &host->h_reclaim);
	list_for_each_entry_safe(fl, next, &host->h_reclaim, fl_u.nfs_fl.list) {
		list_del_init(&fl->fl_u.nfs_fl.list);


		if (signalled())
			continue;
		if (nlmclnt_reclaim(host, fl, req) != 0)
			continue;
		list_add_tail(&fl->fl_u.nfs_fl.list, &host->h_granted);
		if (host->h_nsmstate != nsmstate) {

			goto restart;
		}
	}

	host->h_reclaiming = 0;
	up_write(&host->h_rwsem);
	dprintk("NLM: done reclaiming locks for host %s\n", host->h_name);


	spin_lock(&nlm_blocked_lock);
	list_for_each_entry(block, &nlm_blocked, b_list) {
		if (block->b_host == host) {
			block->b_status = nlm_lck_denied_grace_period;
			wake_up(&block->b_wait);
		}
	}
	spin_unlock(&nlm_blocked_lock);


	nlmclnt_release_host(host);
	lockd_down(net);
	kfree(req);
	return 0;
}
