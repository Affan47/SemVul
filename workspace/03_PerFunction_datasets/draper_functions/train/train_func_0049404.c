gom_action_overall_info(enum gom_info_types std_verb)
{
	int c;
	char * runtime_text[]=
		{
			"",
			"Overall information",
			"-------------------",
			"",
			NULL
		};
	gom_info_text(std_verb, runtime_text);

	gom_info(std_verb, "  Configuration:");
	gom_info(std_verb,
	         "    Mixer special file: %s.",
	         gom_driver_d());
	gom_info(std_verb,
	   "    Fade duration     : %d seconds.",
	   gom_mixer_fadival());
	gom_info(std_verb,
					 "    Gomii refresh     : all %d seconds%s.",
					 gom_gomii_refival(), gom_gomii_refival() == 0 ? " (disabled)" : "");

	gom_info(std_verb,
					 "    Verbosity         : %i [" GOM_INFO_VERBOSITY_PRINTF_MASK "].",
					 gom_info_verbosity(),
					 GOM_INFO_VERBOSITY_PRINTF_VARS);
	gom_info(std_verb,
					 "    Lock mask         : (see table below).");
	gom_info(std_verb,
					 "    Errors detected   : %i.",
					 gom_info_errors);

	gom_info(std_verb, "");
	gom_info(std_verb, "  Current mixer information:");
	gom_info(std_verb,
					 "    Driver used       : %s",
					 gom_driver());
	gom_info(std_verb,
					 "    Available channels: %d / %d",
					 gom_driver_c_len(), gom_driver_C_len());

	gom_info(std_verb, GOM_INFO_TABLE_LINE);
	gom_info(std_verb, GOM_INFO_CHANNEL_INFO_LINE_HEADER);
	gom_info(std_verb, GOM_INFO_TABLE_LINE);

	for (c = gom_driver_c_first(); c > -1; c = gom_driver_c_next(c, 1))
	{
		gom_info_info_help(std_verb, c, 0);
	}
	gom_info(std_verb, GOM_INFO_TABLE_LINE);
	for (c = gom_driver_C_first(); c > -1; c = gom_driver_C_next(c, 1))
	{
		if (!(gom_driver_c (c) > -1)) gom_info_info_help(std_verb, c, 0);
	}
	gom_info(std_verb, GOM_INFO_TABLE_LINE);
	gom_info(std_verb, "    -1 = unavailable, 1 = yes (or value), 0 = no (or value), ");
}
