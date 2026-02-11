callback_alarm_triggered (GtkWidget * size_entry, gpointer data)
{
  gint new_width, new_height;
  gboolean render_success;
  InterfaceIData *p_data = INTERFACE_I_DATA (data);
  CarverData *c_data = p_data->carver_data;


  new_width =
    ROUND (alt_size_entry_get_refval (ALT_SIZE_ENTRY (size_entry), 0));
  new_height =
    ROUND (alt_size_entry_get_refval (ALT_SIZE_ENTRY (size_entry), 1));
  state->new_width = new_width;
  state->new_height = new_height;
  gimp_image_undo_group_start (c_data->image_ID);
  render_success = render_interactive (state, p_data->carver_data);
  gimp_image_undo_group_end (c_data->image_ID);

  if (!render_success)
    {
      dialog_I_response = RESPONSE_FATAL;
      gtk_main_quit();
    }
  gimp_displays_flush();

  set_info_label_text (p_data);


}
