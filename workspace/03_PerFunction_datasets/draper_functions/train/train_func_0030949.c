info_bar_set_progress (GeditTab *tab,
			   goffset   size,
			   goffset   total_size)
{
	if (tab->priv->info_bar == NULL)
		return;

	gedit_debug_message (DEBUG_TAB, "%" G_GUINT64_FORMAT "/%" G_GUINT64_FORMAT, size, total_size);

	g_return_if_fail (GEDIT_IS_PROGRESS_INFO_BAR (tab->priv->info_bar));

	if (total_size == 0)
	{
		if (size != 0)
			gedit_progress_info_bar_pulse (
					GEDIT_PROGRESS_INFO_BAR (tab->priv->info_bar));
		else
			gedit_progress_info_bar_set_fraction (
				GEDIT_PROGRESS_INFO_BAR (tab->priv->info_bar),
				0);
	}
	else
	{
		gdouble frac;

		frac = (gdouble)size / (gdouble)total_size;

		gedit_progress_info_bar_set_fraction (
				GEDIT_PROGRESS_INFO_BAR (tab->priv->info_bar),
				frac);
	}
}
