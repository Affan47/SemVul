get_work_bits(unsigned long *flags)
{
	unsigned long old, new;
	do {
		old = *flags;
		new = old & ~DRBD_DEVICE_WORK_MASK;
	} while (cmpxchg(flags, old, new) != old);
	return old & DRBD_DEVICE_WORK_MASK;
}
