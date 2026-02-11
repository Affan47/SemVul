gpa_date_box_set_date (GpaDateBox *self, GDate *date)
{
  g_return_if_fail (IS_GPA_DATE_BOX (self));

  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->checkbox), !!date);
  gpa_date_button_set_date (GPA_DATE_BUTTON (self->datebtn), date);

  update_widgets (self);
}
