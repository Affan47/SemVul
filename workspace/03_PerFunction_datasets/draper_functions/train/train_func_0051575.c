get_text_secondary_label (GeditDocument *doc)
{
	glong  seconds;
	gchar *secondary_msg;

	seconds = MAX (1, _gedit_document_get_seconds_since_last_save_or_load (doc));

	if (seconds < 55)
	{
		secondary_msg = g_strdup_printf (
					ngettext ("If you don't save, changes from the last %ld second "
					    	  "will be permanently lost.",
						  "If you don't save, changes from the last %ld seconds "
					    	  "will be permanently lost.",
						  seconds),
					seconds);
	}
	else if (seconds < 75)
	{
		secondary_msg = g_strdup (_("If you don't save, changes from the last minute "
					    "will be permanently lost."));
	}
	else if (seconds < 110)
	{
		secondary_msg = g_strdup_printf (
					ngettext ("If you don't save, changes from the last minute and %ld "
						  "second will be permanently lost.",
						  "If you don't save, changes from the last minute and %ld "
						  "seconds will be permanently lost.",
						  seconds - 60 ),
					seconds - 60);
	}
	else if (seconds < 3600)
	{
		secondary_msg = g_strdup_printf (
					ngettext ("If you don't save, changes from the last %ld minute "
					    	  "will be permanently lost.",
						  "If you don't save, changes from the last %ld minutes "
					    	  "will be permanently lost.",
						  seconds / 60),
					seconds / 60);
	}
	else if (seconds < 7200)
	{
		gint minutes;
		seconds -= 3600;

		minutes = seconds / 60;
		if (minutes < 5)
		{
			secondary_msg = g_strdup (_("If you don't save, changes from the last hour "
						    "will be permanently lost."));
		}
		else
		{
			secondary_msg = g_strdup_printf (
					ngettext ("If you don't save, changes from the last hour and %d "
						  "minute will be permanently lost.",
						  "If you don't save, changes from the last hour and %d "
						  "minutes will be permanently lost.",
						  minutes),
					minutes);
		}
	}
	else
	{
		gint hours;

		hours = seconds / 3600;

		secondary_msg = g_strdup_printf (
					ngettext ("If you don't save, changes from the last %d hour "
					    	  "will be permanently lost.",
						  "If you don't save, changes from the last %d hours "
					    	  "will be permanently lost.",
						  hours),
					hours);
	}

	return secondary_msg;
}
