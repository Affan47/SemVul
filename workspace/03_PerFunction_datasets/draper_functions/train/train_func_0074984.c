up_wakeups_perhaps_data_changed (UpWakeups *wakeups)
{
	guint total;


	total = up_wakeups_data_get_total (wakeups);
	if (total != wakeups->priv->total_old) {

		if (wakeups->priv->total_old == 0)
			wakeups->priv->total_ave = total;
		else
			wakeups->priv->total_ave = UP_WAKEUPS_TOTAL_SMOOTH_FACTOR * (gfloat) (total - wakeups->priv->total_old);
		g_signal_emit (wakeups, signals [TOTAL_CHANGED], 0, wakeups->priv->total_ave);
	}


	g_signal_emit (wakeups, signals [DATA_CHANGED], 0);
}
