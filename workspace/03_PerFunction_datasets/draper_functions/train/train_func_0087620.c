mark_lock_irq(struct task_struct *curr, struct held_lock *this,
		enum lock_usage_bit new_bit)
{
	int excl_bit = exclusive_bit(new_bit);
	int read = new_bit & 1;
	int dir = new_bit & 2;


	check_usage_f usage = dir ?
		check_usage_backwards : check_usage_forwards;


	if (!valid_state(curr, this, new_bit, excl_bit))
		return 0;


	if ((!read || !dir || STRICT_READ_CHECKS) &&
			!usage(curr, this, excl_bit, state_name(new_bit & ~1)))
		return 0;


	if (!read) {
		if (!valid_state(curr, this, new_bit, excl_bit + 1))
			return 0;

		if (STRICT_READ_CHECKS &&
			!usage(curr, this, excl_bit + 1,
				state_name(new_bit + 1)))
			return 0;
	}

	if (state_verbose(new_bit, hlock_class(this)))
		return 2;

	return 1;
}
