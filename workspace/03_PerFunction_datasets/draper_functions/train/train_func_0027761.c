select_row_callback (GtkWidget *widget, gint row, gint column,
                     GdkEventButton *event, gpointer data)
{
  gftp_window_data * wdata;

  wdata = data;

  if (event != NULL && event->type == GDK_2BUTTON_PRESS && event->button == 1 &&
      GFTP_IS_CONNECTED (wdata->request) && IS_ONE_SELECTED (wdata))
    list_doaction (wdata);
}
