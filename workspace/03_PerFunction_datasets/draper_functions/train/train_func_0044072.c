iscsi_handle_login_thread_timeout(unsigned long data)
{
	struct iscsi_np *np = (struct iscsi_np *) data;

	spin_lock_bh(&np->np_thread_lock);
	pr_err("iSCSI Login timeout on Network Portal %pISpc\n",
			&np->np_sockaddr);

	if (np->np_login_timer_flags & ISCSI_TF_STOP) {
		spin_unlock_bh(&np->np_thread_lock);
		return;
	}

	if (np->np_thread)
		send_sig(SIGINT, np->np_thread, 1);

	np->np_login_timer_flags &= ~ISCSI_TF_RUNNING;
	spin_unlock_bh(&np->np_thread_lock);
}
