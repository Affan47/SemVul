is_From_line(Mailbox *mbox, gchar *buf)
	{
	gchar	sender[512];
	gint	dayofmonth = 0;

	if (strncmp(buf, "From ", 5))
		return FALSE;


	sender[0] = '\0';
	if (sscanf(buf, "%*s %*s %*s %d", &dayofmonth) != 1)
		{
		if (sscanf(buf, "%*s %511s %*s %*s %d", sender, &dayofmonth) != 2)
			return FALSE;
		}
	if (dayofmonth < 1 || dayofmonth > 31)
		return FALSE;
	if (strcmp(sender, "MAILER-DAEMON") == 0)
		mbox->is_internal = TRUE;
	return TRUE;
	}
