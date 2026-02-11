mthca_buddy_init(struct mthca_buddy *buddy, int max_order)
{
	int i, s;

	buddy->max_order = max_order;
	spin_lock_init(&buddy->lock);

	buddy->bits = kzalloc((buddy->max_order + 1) * sizeof (long *),
			      GFP_KERNEL);
	buddy->num_free = kcalloc((buddy->max_order + 1), sizeof *buddy->num_free,
				  GFP_KERNEL);
	if (!buddy->bits || !buddy->num_free)
		goto err_out;

	for (i = 0; i <= buddy->max_order; ++i) {
		s = BITS_TO_LONGS(1 << (buddy->max_order - i));
		buddy->bits[i] = kmalloc(s * sizeof (long), GFP_KERNEL);
		if (!buddy->bits[i])
			goto err_out_free;
		bitmap_zero(buddy->bits[i],
			    1 << (buddy->max_order - i));
	}

	set_bit(0, buddy->bits[buddy->max_order]);
	buddy->num_free[buddy->max_order] = 1;

	return 0;

err_out_free:
	for (i = 0; i <= buddy->max_order; ++i)
		kfree(buddy->bits[i]);

err_out:
	kfree(buddy->bits);
	kfree(buddy->num_free);

	return -ENOMEM;
}
