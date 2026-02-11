sst25l_wait_till_ready(struct sst25l_flash *flash)
{
	unsigned long deadline;
	int status, err;

	deadline = jiffies + MAX_READY_WAIT_JIFFIES;
	do {
		err = sst25l_status(flash, &status);
		if (err)
			return err;
		if (!(status & SST25L_STATUS_BUSY))
			return 0;

		cond_resched();
	} while (!time_after_eq(jiffies, deadline));

	return -ETIMEDOUT;
}
