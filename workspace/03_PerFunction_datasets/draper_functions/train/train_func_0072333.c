cb_chart_release(GtkWidget *widget, GdkEventButton *ev, NetMon *net)
	{
	if (!net->reset_button_in && !net->stats_button_in)
		return FALSE;
	if (net->stats_button_in && gkrellm_in_decal(decal_stats, ev))
		net_stats_window_show(net);
	if (net->reset_button_in && gkrellm_in_decal(decal_reset, ev))
		{
		if (net->show_totalB)
			net->rx_totalB = net->tx_totalB = 0;
		else
			net->rx_totalA = net->tx_totalA = 0;
		}
	net->reset_button_in = FALSE;
	net->stats_button_in = FALSE;
	refresh_net_chart(net);
	return FALSE;
	}
