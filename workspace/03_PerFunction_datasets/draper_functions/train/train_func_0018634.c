on_button_release  (GtkWidget       *win,
                    GdkEventButton  *ev,
                    gpointer         user_data)
{
  AnnotateData *data = (AnnotateData *) user_data;


  AnnotateDeviceData *devdata = g_hash_table_lookup(data->devdatatable, ev->device);

  guint lenght = g_slist_length (devdata->coord_list);

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
      g_printerr ("Device '%s': Button %i Up at (x,y)= (%.2f : %.2f)\n",
                   gdk_device_get_name (ev->device),
                   ev->button, ev->x, ev->y);
    }

#ifdef _WIN32
  if (inside_bar_window (ev->x_root, ev->y_root))

    {

      annotate_release_grab ();
      return FALSE;
    }
  if (data->old_paint_type == ANNOTATE_PEN)
    {
      annotate_select_pen ();
    }
#endif

  initialize_annotation_cairo_context(data);

  if (lenght > 2)
    {
      AnnotatePoint *first_point = (AnnotatePoint *) g_slist_nth_data (devdata->coord_list, lenght-1);
      AnnotatePoint *last_point = (AnnotatePoint *) g_slist_nth_data (devdata->coord_list, 0);

      gdouble distance = get_distance (ev->x, ev->y, first_point->x, first_point->y);


      gint score = 3;


      if ((data->rectify || data->roundify))
        {
          score = 6;
        }

      gdouble tollerance = annotate_get_thickness () * score;

      gdouble pressure = last_point->pressure;

      gboolean closed_path = FALSE;


      if (distance > tollerance)
        {

          annotate_draw_line (devdata, ev->x, ev->y, TRUE);
          annotate_coord_list_prepend (devdata, ev->x, ev->y, annotate_get_thickness (), pressure);
        }
      else
        {

          closed_path = TRUE;
          annotate_draw_line (devdata, first_point->x, first_point->y, TRUE);
          annotate_coord_list_prepend (devdata, first_point->x, first_point->y, annotate_get_thickness (), pressure);
        }

      if (data->cur_context->type != ANNOTATE_ERASER)
        {
          annotate_shape_recognize (devdata, closed_path);


          if (data->arrow)
            {

              annotate_draw_arrow (devdata, distance);
            }
        }
    }

  cairo_stroke_preserve (data->annotation_cairo_context);

  annotate_add_savepoint ();

  annotate_hide_cursor ();

  return TRUE;
}
