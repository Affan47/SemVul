gromit_clear_screen (GromitData *data)
{
  gdk_gc_set_foreground (data->shape_gc, data->transparent);
  gdk_draw_rectangle (data->shape, data->shape_gc, 1,
                      0, 0, data->width, data->height);
  gtk_widget_shape_combine_mask (data->win, data->shape, 0,0);
  if (!data->hard_grab)
    gromit_hide_window (data);
  data->painted = 0;
}
