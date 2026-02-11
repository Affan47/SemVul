on_button_press    (GtkWidget      *win,
                    GdkEventButton *ev,
                    gpointer        user_data)
{

  AnnotateData *data = (AnnotateData *) user_data;


  AnnotateDeviceData *devdata = g_hash_table_lookup(data->devdatatable, ev->device);

  gdouble pressure = 1.0;

  if (!data->is_grabbed)
    {
      return FALSE;
	}

  if (!ev)
    {
      g_printerr ("Device '%s': Invalid event; I ungrab all\n",
                   gdk_device_get_name (ev->device));
      annotate_release_grab ();
      return FALSE;
    }

  if (data->debug)
    {
      g_printerr ("Device '%s': Button %i Down at (x,y)= (%f : %f)\n",
                  gdk_device_get_name (ev->device),
                  ev->button,
                  ev->x,
                  ev->y);
    }

#ifdef _WIN32
  if (inside_bar_window (ev->x_root, ev->y_root))
    {

      annotate_release_grab ();
      return FALSE;
    }

  if (data->cur_context->type == ANNOTATE_PEN)
    {
      annotate_select_tool (data, ev->device, ev->state);
      data->old_paint_type = ANNOTATE_PEN;
    }
  else
    {
      data->old_paint_type = ANNOTATE_ERASER;
    }
#endif

  pressure = get_pressure ( (GdkEvent *) ev);

  if (pressure <= 0)
    {
      return FALSE;
    }

  initialize_annotation_cairo_context(data);

  annotate_configure_pen_options (data);

  annotate_coord_dev_list_free (devdata);

  annotate_unhide_cursor ();

  annotate_draw_point (devdata, ev->x, ev->y, pressure);

  annotate_coord_list_prepend (devdata,
                               ev->x,
                               ev->y,
                               annotate_get_thickness (),
                               pressure);

  return TRUE;
}
