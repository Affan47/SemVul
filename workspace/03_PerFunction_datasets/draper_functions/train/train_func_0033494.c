ntfs_rl_mm(runlist_element *base, int dst, int src,
		int size)
{
	if (likely((dst != src) && (size > 0)))
		memmove(base + dst, base + src, size * sizeof(*base));
}
