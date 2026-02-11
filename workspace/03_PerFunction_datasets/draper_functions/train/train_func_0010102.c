watchdog_stop(void)
{
	int err = 0;

	mutex_lock(&watchdog.lock);
	err = superio_enter(watchdog.sioaddr);
	if (err)
		goto exit_unlock;
	superio_select(watchdog.sioaddr, SIO_F71808FG_LD_WDT);

	superio_clear_bit(watchdog.sioaddr, F71808FG_REG_WDT_CONF,
			F71808FG_FLAG_WD_EN);

	superio_exit(watchdog.sioaddr);

exit_unlock:
	mutex_unlock(&watchdog.lock);

	return err;
}
