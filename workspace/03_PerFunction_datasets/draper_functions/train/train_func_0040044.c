lgdt3306a_sync_lock_poll(struct lgdt3306a_state *state)
{
	enum lgdt3306a_lock_status syncLockStatus = LG3306_UNLOCK;
	int	i;

	for (i = 0; i < 2; i++)	{
		msleep(30);

		syncLockStatus = lgdt3306a_check_lock_status(state,
							     LG3306_SYNC_LOCK);

		if (syncLockStatus == LG3306_LOCK) {
			dbg_info("locked(%d)\n", i);
			return LG3306_LOCK;
		}
	}
	dbg_info("not locked\n");
	return LG3306_UNLOCK;
}
