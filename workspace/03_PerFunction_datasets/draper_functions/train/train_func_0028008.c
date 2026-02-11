encode_tail(int cpu, int idx)
{
	u32 tail;

#ifdef CONFIG_DEBUG_SPINLOCK
	BUG_ON(idx > 3);
#endif
	tail  = (cpu + 1) << _Q_TAIL_CPU_OFFSET;
	tail |= idx << _Q_TAIL_IDX_OFFSET;

	return tail;
}
