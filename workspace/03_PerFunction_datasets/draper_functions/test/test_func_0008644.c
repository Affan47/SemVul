proximity_out (GtkWidget *win, GdkEventProximity *ev, gpointer user_data)
{
  GromitData *data = (GromitData *) user_data;

  data->cur_context = data->default_pen;

  if (data->cur_context->type == GROMIT_ERASER)
    gdk_window_set_cursor (data->win->window, data->erase_cursor);
  else
    gdk_window_set_cursor (data->win->window, data->paint_cursor);

  data->state = 0;
  data->device = NULL;

  return FALSE;
}
