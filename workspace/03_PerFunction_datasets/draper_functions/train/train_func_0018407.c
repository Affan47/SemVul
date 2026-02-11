linux_wlan_lock_timeout(void *vp, u32 timeout)
{
	int error = -1;

	PRINT_D(LOCK_DBG, "Locking %p\n", vp);
	if (vp != NULL)
		error = down_timeout((struct semaphore *)vp, msecs_to_jiffies(timeout));
	else
		PRINT_ER("Failed, mutex is NULL\n");
	return error;
}
