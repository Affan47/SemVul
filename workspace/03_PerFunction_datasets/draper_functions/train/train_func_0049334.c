do_pd_read_start(void)
{
	if (pd_wait_for(pd_current, STAT_READY, "do_pd_read") & STAT_ERR) {
		if (pd_retries < PD_MAX_RETRIES) {
			pd_retries++;
			return Wait;
		}
		return Fail;
	}
	pd_ide_command(pd_current, IDE_READ, pd_block, pd_run);
	phase = do_pd_read_drq;
	pd_timeout = jiffies + PD_TMO;
	return Hold;
}
