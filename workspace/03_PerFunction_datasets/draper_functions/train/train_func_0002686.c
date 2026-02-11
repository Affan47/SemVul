clockid_to_kclock(const clockid_t id)
{
	if (id < 0)
		return (id & CLOCKFD_MASK) == CLOCKFD ?
			&clock_posix_dynamic : &clock_posix_cpu;

	if (id >= MAX_CLOCKS || !posix_clocks[id].clock_getres)
		return NULL;
	return &posix_clocks[id];
}
