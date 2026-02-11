mmc_poweroff_notify(struct mmc_card *card, unsigned int notify_type)
{
	unsigned int timeout = card->ext_csd.generic_cmd6_time;
	int err;


	if (notify_type == EXT_CSD_POWER_OFF_LONG)
		timeout = card->ext_csd.power_off_longtime;

	err = __mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
			EXT_CSD_POWER_OFF_NOTIFICATION,
			notify_type, timeout, true, false, false);
	if (err)
		pr_err("%s: Power Off Notification timed out, %u\n",
		       mmc_hostname(card->host), timeout);


	card->ext_csd.power_off_notification = EXT_CSD_NO_POWER_NOTIFICATION;

	return err;
}
