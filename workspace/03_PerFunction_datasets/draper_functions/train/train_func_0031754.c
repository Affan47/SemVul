rl_transpose_chars (count, key)
     int count, key;
{
#if defined (HANDLE_MULTIBYTE)
  char *dummy;
  int i;
#else
  char dummy[2];
#endif
  int char_length, prev_point;

  if (count == 0)
    return 0;

  if (!rl_point || rl_end < 2)
    {
      rl_ding ();
      return -1;
    }

  rl_begin_undo_group ();

  if (rl_point == rl_end)
    {
      rl_point = MB_PREVCHAR (rl_line_buffer, rl_point, MB_FIND_NONZERO);
      count = 1;
    }

  prev_point = rl_point;
  rl_point = MB_PREVCHAR (rl_line_buffer, rl_point, MB_FIND_NONZERO);

#if defined (HANDLE_MULTIBYTE)
  char_length = prev_point - rl_point;
  dummy = (char *)xmalloc (char_length + 1);
  for (i = 0; i < char_length; i++)
    dummy[i] = rl_line_buffer[rl_point + i];
  dummy[i] = '\0';
#else
  dummy[0] = rl_line_buffer[rl_point];
  dummy[char_length = 1] = '\0';
#endif

  rl_delete_text (rl_point, rl_point + char_length);

  rl_point = _rl_find_next_mbchar (rl_line_buffer, rl_point, count, MB_FIND_NONZERO);

  _rl_fix_point (0);
  rl_insert_text (dummy);
  rl_end_undo_group ();

#if defined (HANDLE_MULTIBYTE)
  xfree (dummy);
#endif

  return 0;
}
