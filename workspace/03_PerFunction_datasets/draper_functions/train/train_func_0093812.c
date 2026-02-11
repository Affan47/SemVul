show_stuff(char *user, int t1, int t2)
{
    BOOL can_show = FALSE;
    char formatter[80];

    if (local_finger) {
	if (prog_config.local_config_bits1 & t1)
	    can_show = TRUE;
    } else {
	if (prog_config.config_bits1 & t1)
	    can_show = TRUE;
    }

    if (can_show) {
	columns++;
	snprintf(formatter, sizeof(formatter), "%%s%%-%d.%ds", (36 - strlen(prog_config.p_strings[t2])),
		36);
	printf(formatter, prog_config.p_strings[t2], user?user:"");
	do_columns();
    }
}
