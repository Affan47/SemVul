ops_complete_reconstruct(void *stripe_head_ref)
{
	struct stripe_head *sh = stripe_head_ref;
	int disks = sh->disks;
	int pd_idx = sh->pd_idx;
	int qd_idx = sh->qd_idx;
	int i;
	bool fua = false, sync = false, discard = false;

	pr_debug("%s: stripe %llu\n", __func__,
		(unsigned long long)sh->sector);

	for (i = disks; i--; ) {
		fua |= test_bit(R5_WantFUA, &sh->dev[i].flags);
		sync |= test_bit(R5_SyncIO, &sh->dev[i].flags);
		discard |= test_bit(R5_Discard, &sh->dev[i].flags);
	}

	for (i = disks; i--; ) {
		struct r5dev *dev = &sh->dev[i];

		if (dev->written || i == pd_idx || i == qd_idx) {
			if (!discard && !test_bit(R5_SkipCopy, &dev->flags)) {
				set_bit(R5_UPTODATE, &dev->flags);
				if (test_bit(STRIPE_EXPAND_READY, &sh->state))
					set_bit(R5_Expanded, &dev->flags);
			}
			if (fua)
				set_bit(R5_WantFUA, &dev->flags);
			if (sync)
				set_bit(R5_SyncIO, &dev->flags);
		}
	}

	if (sh->reconstruct_state == reconstruct_state_drain_run)
		sh->reconstruct_state = reconstruct_state_drain_result;
	else if (sh->reconstruct_state == reconstruct_state_prexor_drain_run)
		sh->reconstruct_state = reconstruct_state_prexor_drain_result;
	else {
		BUG_ON(sh->reconstruct_state != reconstruct_state_run);
		sh->reconstruct_state = reconstruct_state_result;
	}

	set_bit(STRIPE_HANDLE, &sh->state);
	raid5_release_stripe(sh);
}
