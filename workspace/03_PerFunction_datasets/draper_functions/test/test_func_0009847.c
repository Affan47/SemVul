gx_rack_tuner_check_poll(GxRackTuner *tuner)
{
	if (gtk_widget_get_sensitive(GTK_WIDGET(tuner)) && gtk_widget_get_mapped(GTK_WIDGET(tuner))) {
		if (!tuner->freqpoll_id) {
			tuner->freqpoll_id = gdk_threads_add_timeout(
				tuner->timestep, gx_rack_tuner_freq_poll_handler, tuner);
			g_signal_emit_by_name(tuner, "poll-status-changed", TRUE);
			gx_rack_tuner_freq_poll_handler(tuner);
		}
	} else {
		gx_rack_tuner_remove_handler(tuner);
	}
}
