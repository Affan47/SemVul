try_to_extend_reservation(struct ext2_reserve_window_node *my_rsv,
			struct super_block *sb, int size)
{
	struct ext2_reserve_window_node *next_rsv;
	struct rb_node *next;
	spinlock_t *rsv_lock = &EXT2_SB(sb)->s_rsv_window_lock;

	if (!spin_trylock(rsv_lock))
		return;

	next = rb_next(&my_rsv->rsv_node);

	if (!next)
		my_rsv->rsv_end += size;
	else {
		next_rsv = rb_entry(next, struct ext2_reserve_window_node, rsv_node);

		if ((next_rsv->rsv_start - my_rsv->rsv_end - 1) >= size)
			my_rsv->rsv_end += size;
		else
			my_rsv->rsv_end = next_rsv->rsv_start - 1;
	}
	spin_unlock(rsv_lock);
}
