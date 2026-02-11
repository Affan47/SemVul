ipmi_register_for_cmd(ipmi_user_t   user,
			  unsigned char netfn,
			  unsigned char cmd,
			  unsigned int  chans)
{
	ipmi_smi_t      intf = user->intf;
	struct cmd_rcvr *rcvr;
	int             rv = 0;


	rcvr = kmalloc(sizeof(*rcvr), GFP_KERNEL);
	if (!rcvr)
		return -ENOMEM;
	rcvr->cmd = cmd;
	rcvr->netfn = netfn;
	rcvr->chans = chans;
	rcvr->user = user;

	mutex_lock(&intf->cmd_rcvrs_mutex);

	if (!is_cmd_rcvr_exclusive(intf, netfn, cmd, chans)) {
		rv = -EBUSY;
		goto out_unlock;
	}

	if (atomic_inc_return(&intf->event_waiters) == 1)
		need_waiter(intf);

	list_add_rcu(&rcvr->link, &intf->cmd_rcvrs);

 out_unlock:
	mutex_unlock(&intf->cmd_rcvrs_mutex);
	if (rv)
		kfree(rcvr);

	return rv;
}
