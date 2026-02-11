almanah_calendar_button_day_selected_cb (GtkCalendar *calendar, AlmanahCalendarButton *self)
{
	GDate calendar_date;
	gchar calendar_string[100];

	almanah_calendar_get_date (self->priv->calendar, &calendar_date);

	g_date_strftime (calendar_string, sizeof (calendar_string), _("%A, %e %B %Y"), &calendar_date);
	gtk_label_set_text (GTK_LABEL (self->priv->label), calendar_string);
	if (self->priv->user_event < DAY_EVENT) {

		self->priv->user_event = DAY_EVENT;
		almanah_calendar_window_popdown (ALMANAH_CALENDAR_WINDOW (self->priv->dock));
	}

	self->priv->user_event = NONE_EVENT;


	g_signal_emit (self, calendar_button_signals[DAY_SELECTED_SIGNAL], 0);
}
