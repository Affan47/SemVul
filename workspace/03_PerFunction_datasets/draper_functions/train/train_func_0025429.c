ubi_wl_scrub_peb(struct ubi_device *ubi, int pnum)
{
	struct ubi_wl_entry *e;

	ubi_msg(ubi, "schedule PEB %d for scrubbing", pnum);

retry:
	spin_lock(&ubi->wl_lock);
	e = ubi->lookuptbl[pnum];
	if (e == ubi->move_from || in_wl_tree(e, &ubi->scrub) ||
				   in_wl_tree(e, &ubi->erroneous)) {
		spin_unlock(&ubi->wl_lock);
		return 0;
	}

	if (e == ubi->move_to) {


		spin_unlock(&ubi->wl_lock);
		dbg_wl("the PEB %d is not in proper tree, retry", pnum);
		yield();
		goto retry;
	}

	if (in_wl_tree(e, &ubi->used)) {
		self_check_in_wl_tree(ubi, e, &ubi->used);
		rb_erase(&e->u.rb, &ubi->used);
	} else {
		int err;

		err = prot_queue_del(ubi, e->pnum);
		if (err) {
			ubi_err(ubi, "PEB %d not found", pnum);
			ubi_ro_mode(ubi);
			spin_unlock(&ubi->wl_lock);
			return err;
		}
	}

	wl_tree_add(e, &ubi->scrub);
	spin_unlock(&ubi->wl_lock);


	return ensure_wear_leveling(ubi, 0);
}
