prot_queue_del(struct ubi_device *ubi, int pnum)
{
	struct ubi_wl_entry *e;

	e = ubi->lookuptbl[pnum];
	if (!e)
		return -ENODEV;

	if (self_check_in_pq(ubi, e))
		return -ENODEV;

	list_del(&e->u.list);
	dbg_wl("deleted PEB %d from the protection queue", e->pnum);
	return 0;
}
