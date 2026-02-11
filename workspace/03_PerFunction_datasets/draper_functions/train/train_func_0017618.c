wl_get_wle(struct ubi_device *ubi)
{
	struct ubi_wl_entry *e;

	e = find_mean_wl_entry(ubi, &ubi->free);
	if (!e) {
		ubi_err(ubi, "no free eraseblocks");
		return NULL;
	}

	self_check_in_wl_tree(ubi, e, &ubi->free);


	rb_erase(&e->u.rb, &ubi->free);
	ubi->free_count--;
	dbg_wl("PEB %d EC %d", e->pnum, e->ec);

	return e;
}
