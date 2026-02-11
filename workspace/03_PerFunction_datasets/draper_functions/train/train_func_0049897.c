plip_bh(struct work_struct *work)
{
	struct net_local *nl = container_of(work, struct net_local, immediate);
	struct plip_local *snd = &nl->snd_data;
	struct plip_local *rcv = &nl->rcv_data;
	plip_func f;
	int r;

	nl->is_deferred = 0;
	f = connection_state_table[nl->connection];
	if ((r = (*f)(nl->dev, nl, snd, rcv)) != OK &&
	    (r = plip_bh_timeout_error(nl->dev, nl, snd, rcv, r)) != OK) {
		nl->is_deferred = 1;
		schedule_delayed_work(&nl->deferred, 1);
	}
}
