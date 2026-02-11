tgt_bind_host_to_target(int tid, int host_no)
{
	struct target *target;
	struct bound_host *bhost;

	target = target_lookup(tid);
	if (!target) {
		eprintf("can't find a target %d\n", tid);
		return -ENOENT;
	}

	list_for_each_entry(bhost, &bound_host_list, bhost_siblings) {
		if (bhost->host_no == host_no) {
			eprintf("already bound %d\n", host_no);
			return -EINVAL;
		}
	}

	bhost = malloc(sizeof(*bhost));
	if (!bhost)
		return -ENOMEM;

	bhost->host_no = host_no;
	bhost->target = target;

	list_add(&bhost->bhost_siblings, &bound_host_list);

	dprintf("bound the scsi host %d to the target %d\n", host_no, tid);

	return 0;
}
