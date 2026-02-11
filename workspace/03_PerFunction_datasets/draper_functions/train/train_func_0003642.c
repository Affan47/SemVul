channel_combo_box_changed_cb (GtkComboBox *combo_box,
			      gpointer     user_data)
{
	GthHistogramView *self = user_data;
	int               n_channel;

	n_channel = gtk_combo_box_get_active (combo_box);
	if (n_channel < GTH_HISTOGRAM_N_CHANNELS) {
		gth_histogram_view_set_current_channel (GTH_HISTOGRAM_VIEW (self), n_channel);
		gth_histogram_view_set_display_mode (GTH_HISTOGRAM_VIEW (self), GTH_HISTOGRAM_MODE_ONE_CHANNEL);
	}
	else
		gth_histogram_view_set_display_mode (GTH_HISTOGRAM_VIEW (self), GTH_HISTOGRAM_MODE_ALL_CHANNELS);
}
