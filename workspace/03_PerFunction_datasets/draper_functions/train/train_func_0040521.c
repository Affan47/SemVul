check_split(void)
{
	if ((bootopt & BOOT_STANDALONE))
		return;

	if (istat.is_eobservers < iconf.split_minservers ||
	    istat.is_user[0] + istat.is_user[1] < iconf.split_minusers)
	{

		if (!IsSplit())
		{
			sendto_flag(SCH_NOTICE,
				"Network split detected, split mode activated");
			iconf.split = timeofday;
		}
	}
	else
	{

		if (IsSplit())
		{
			sendto_flag(SCH_NOTICE,
				"Network rejoined, split mode deactivated");
			iconf.split = 0;
			if (!firstrejoindone)
			{
				firstrejoindone = 1;
				activate_delayed_listeners();
#ifdef CACCEPT_DEFAULT
				iconf.caccept = CACCEPT_DEFAULT;
#endif
			}
		}
	}
}
