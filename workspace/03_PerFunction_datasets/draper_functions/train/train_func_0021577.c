handle_stripe_fill(struct stripe_head *sh,
			       struct stripe_head_state *s,
			       int disks)
{
	int i;


	if (!test_bit(STRIPE_COMPUTE_RUN, &sh->state) && !sh->check_state &&
	    !sh->reconstruct_state)
		for (i = disks; i--; )
			if (fetch_block(sh, s, i, disks))
				break;
	set_bit(STRIPE_HANDLE, &sh->state);
}
