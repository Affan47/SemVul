dialogs_set_sensitive (gboolean sensitive)
{
  int i;
  gtk_widget_set_sensitive (color_adjust_dialog, sensitive);
  gtk_widget_set_sensitive (setup_dialog, sensitive);
  gtk_widget_set_sensitive (print_dialog, sensitive);
  gtk_widget_set_sensitive (new_printer_dialog, sensitive);
  gtk_widget_set_sensitive (about_dialog, sensitive);
  for (i = 0; i < current_option_count; i++)
    {
      if (current_options[i].fast_desc->p_type == STP_PARAMETER_TYPE_CURVE &&
	  current_options[i].info.curve.dialog)
	gtk_widget_set_sensitive(current_options[i].info.curve.dialog,
				 sensitive);
    }
}
