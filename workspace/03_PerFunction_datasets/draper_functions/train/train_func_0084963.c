clutter_text_move_word_backward (ClutterText *self,
                                 gint         start)
{
  gint retval = start;

  if (clutter_text_buffer_get_length (get_buffer (self)) > 0 && start > 0)
    {
      PangoLayout *layout = clutter_text_get_layout (self);
      PangoLogAttr *log_attrs = NULL;
      gint n_attrs = 0;

      pango_layout_get_log_attrs (layout, &log_attrs, &n_attrs);

      retval = start - 1;
      while (retval > 0 && !log_attrs[retval].is_word_start)
        retval -= 1;

      g_free (log_attrs);
    }

  return retval;
}
