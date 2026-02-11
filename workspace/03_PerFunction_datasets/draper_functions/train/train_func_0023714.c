ubi_wl_put_peb(struct ubi_device *ubi, int vol_id, int lnum,
		   int pnum, int torture)
{
	int err;
	struct ubi_wl_entry *e;

	dbg_wl("PEB %d", pnum);
	ubi_assert(pnum >= 0);
	ubi_assert(pnum < ubi->peb_count);

	down_read(&ubi->fm_protect);

retry:
	spin_lock(&ubi->wl_lock);
	e = ubi->lookuptbl[pnum];
	if (e == ubi->move_from) {


		dbg_wl("PEB %d is being moved, wait", pnum);
		spin_unlock(&ubi->wl_lock);


		mutex_lock(&ubi->move_mutex);
		mutex_unlock(&ubi->move_mutex);
		goto retry;
	} else if (e == ubi->move_to) {


		dbg_wl("PEB %d is the target of data moving", pnum);
		ubi_assert(!ubi->move_to_put);
		ubi->move_to_put = 1;
		spin_unlock(&ubi->wl_lock);
		up_read(&ubi->fm_protect);
		return 0;
	} else {
		if (in_wl_tree(e, &ubi->used)) {
			self_check_in_wl_tree(ubi, e, &ubi->used);
			rb_erase(&e->u.rb, &ubi->used);
		} else if (in_wl_tree(e, &ubi->scrub)) {
			self_check_in_wl_tree(ubi, e, &ubi->scrub);
			rb_erase(&e->u.rb, &ubi->scrub);
		} else if (in_wl_tree(e, &ubi->erroneous)) {
			self_check_in_wl_tree(ubi, e, &ubi->erroneous);
			rb_erase(&e->u.rb, &ubi->erroneous);
			ubi->erroneous_peb_count -= 1;
			ubi_assert(ubi->erroneous_peb_count >= 0);

			torture = 1;
		} else {
			err = prot_queue_del(ubi, e->pnum);
			if (err) {
				ubi_err(ubi, "PEB %d not found", pnum);
				ubi_ro_mode(ubi);
				spin_unlock(&ubi->wl_lock);
				up_read(&ubi->fm_protect);
				return err;
			}
		}
	}
	spin_unlock(&ubi->wl_lock);

	err = schedule_erase(ubi, e, vol_id, lnum, torture);
	if (err) {
		spin_lock(&ubi->wl_lock);
		wl_tree_add(e, &ubi->used);
		spin_unlock(&ubi->wl_lock);
	}

	up_read(&ubi->fm_protect);
	return err;
}
