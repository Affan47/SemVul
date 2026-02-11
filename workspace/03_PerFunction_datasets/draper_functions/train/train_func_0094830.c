il_setup_watchdog(struct il_priv *il)
{
	unsigned int timeout = il->cfg->wd_timeout;

	if (timeout)
		mod_timer(&il->watchdog,
			  jiffies + msecs_to_jiffies(IL_WD_TICK(timeout)));
	else
		del_timer(&il->watchdog);
}
