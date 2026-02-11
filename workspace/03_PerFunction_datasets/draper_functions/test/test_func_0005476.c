line_type_dialog_response(GtkWidget *widget, gint response,
                               struct line_type_data *line_type_data)
{
  switch (response) {
  case GTK_RESPONSE_REJECT:
  case GTK_RESPONSE_DELETE_EVENT:

    break;
  case GTK_RESPONSE_ACCEPT:
    line_type_dialog_ok(widget, line_type_data);
    break;
  default:
    printf("line_type_dialog_response(): strange signal %d\n",response);
  }

  i_set_state (line_type_data->w_current, SELECT);
  i_update_toolbar (line_type_data->w_current);
  gtk_widget_destroy (line_type_data->dialog);

  g_free (line_type_data);
}
