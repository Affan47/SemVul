st_im_text_delete_surrounding_cb (GtkIMContext *context,
                                  gint          offset,
                                  gint          n_chars,
                                  StIMText     *imtext)
{
  ClutterText *clutter_text = CLUTTER_TEXT (imtext);

  if (clutter_text_get_editable (clutter_text))
    {
      gint cursor_pos = clutter_text_get_cursor_position (clutter_text);
      clutter_text_delete_text (clutter_text,
                                cursor_pos + offset,
                                cursor_pos + offset + n_chars);
    }

  return TRUE;
}
