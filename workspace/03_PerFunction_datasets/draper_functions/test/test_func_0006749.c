mlx4_buddy_init(struct mlx4_buddy *buddy, int max_order)
{
	int i, s;

	buddy->max_order = max_order;
	spin_lock_init(&buddy->lock);

	buddy->bits = kcalloc(buddy->max_order + 1, sizeof (long *),
			      GFP_KERNEL);
	buddy->num_free = kcalloc((buddy->max_order + 1), sizeof *buddy->num_free,
				  GFP_KERNEL);
	if (!buddy->bits || !buddy->num_free)
		goto err_out;

	for (i = 0; i <= buddy->max_order; ++i) {
		s = BITS_TO_LONGS(1 << (buddy->max_order - i));
		buddy->bits[i] = kcalloc(s, sizeof (long), GFP_KERNEL | __GFP_NOWARN);
		if (!buddy->bits[i]) {
			buddy->bits[i] = vzalloc(s * sizeof(long));
			if (!buddy->bits[i])
				goto err_out_free;
		}
	}

	set_bit(0, buddy->bits[buddy->max_order]);
	buddy->num_free[buddy->max_order] = 1;

	return 0;

err_out_free:
	for (i = 0; i <= buddy->max_order; ++i)
		kvfree(buddy->bits[i]);

err_out:
	kfree(buddy->bits);
	kfree(buddy->num_free);

	return -ENOMEM;
}
