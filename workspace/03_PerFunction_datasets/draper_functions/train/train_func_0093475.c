__fd_set(const int fd, int dir)
{
	uint32_t ofs = FD2OFS(fd);
	uint32_t dmsk = DIR2MSK(dir);
	uint32_t old_evt;

	old_evt = fd_evts[ofs] >> FD2BIT(fd);
	old_evt &= 3;
	if (unlikely(old_evt & dmsk))
		return 0;

	alloc_chg_list(fd, old_evt);
	dmsk <<= FD2BIT(fd);
	fd_evts[ofs] |= dmsk;
	return 1;
}
