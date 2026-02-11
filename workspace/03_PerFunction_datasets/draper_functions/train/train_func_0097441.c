bnx2x_exe_queue_add(struct bnx2x *bp,
				      struct bnx2x_exe_queue_obj *o,
				      struct bnx2x_exeq_elem *elem,
				      bool restore)
{
	int rc;

	spin_lock_bh(&o->lock);

	if (!restore) {

		rc = o->optimize(bp, o->owner, elem);
		if (rc)
			goto free_and_exit;


		rc = o->validate(bp, o->owner, elem);
		if (rc) {
			DP(BNX2X_MSG_SP, "Preamble failed: %d\n", rc);
			goto free_and_exit;
		}
	}


	list_add_tail(&elem->link, &o->exe_queue);

	spin_unlock_bh(&o->lock);

	return 0;

free_and_exit:
	bnx2x_exe_queue_free_elem(bp, elem);

	spin_unlock_bh(&o->lock);

	return rc;
}
