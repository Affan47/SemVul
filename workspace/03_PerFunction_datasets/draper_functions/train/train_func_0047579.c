display_info_keyseq (int expecting_future_input)
{
  char *rep;

  rep = pretty_keyseq (info_keyseq);
  if (expecting_future_input)
    strcat (rep, "-");

  if (echo_area_is_active)
    inform_in_echo_area (rep);
  else
    {
      window_message_in_echo_area (rep, NULL, NULL);
      display_cursor_at_point (active_window);
    }
  info_keyseq_displayed_p = 1;
}
