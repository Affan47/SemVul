day_selected_cb (GtkWidget *widget, gpointer user_data)
{
  GpaDateButton *self = GPA_DATE_BUTTON (user_data);

  if (self->ignore_next_selection)
    {
      self->ignore_next_selection = 0;
      return;
    }

  gtk_calendar_get_date (GTK_CALENDAR (self->calendar),
                         &self->current_year,
                         &self->current_month,
                         &self->current_day);
  self->current_month++;
  update_widgets (self);

  g_signal_emit_by_name (self, "date-set");

  gtk_widget_destroy (self->dialog);
}
