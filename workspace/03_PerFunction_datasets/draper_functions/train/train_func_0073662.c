clutter_text_set_selection (ClutterText *self,
                            gssize       start_pos,
                            gssize       end_pos)
{
  guint n_chars;

  g_return_if_fail (CLUTTER_IS_TEXT (self));

  n_chars = clutter_text_buffer_get_length (get_buffer (self));
  if (end_pos < 0)
    end_pos = n_chars;

  start_pos = MIN (n_chars, start_pos);
  end_pos = MIN (n_chars, end_pos);

  clutter_text_set_positions (self, start_pos, end_pos);
}
