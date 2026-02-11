gkrellm_start_timer(gint Hz)
	{
	static gint	timeout_id	= 0;
	gint		interval;

	if (timeout_id)
		gtk_timeout_remove(timeout_id);
	timeout_id = 0;
	if (Hz > 0)
		{
		interval = 1000 / Hz;
		interval = interval * 60 / 63;
		timeout_id = gtk_timeout_add(interval,
						(GtkFunction) update_monitors,NULL);
		}
	}
