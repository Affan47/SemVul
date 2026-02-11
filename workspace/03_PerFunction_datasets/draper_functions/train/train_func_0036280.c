log_recovery(struct log *l, struct skiplist *list)
{
	int sizes = lseek(l->fd, 0, SEEK_END);
	if (sizes > 0)
		__DEBUG("%s", "WARNING: Find log file,need to recover");

	return 0;
}
