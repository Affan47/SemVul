showbars(gboolean state)
{
	if (state)
	{
		gtk_widget_show(sidebar_vbox_bars);
		if (!CONFIG_SHOW_BARS)
			CONFIG_SHOW_BARS = 1;
	}
	else
	{
		gtk_widget_hide(sidebar_vbox_bars);
		CONFIG_SHOW_BARS = 0;
	}

	save_settings();
}
