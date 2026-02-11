cmd_info (int interactive UNUSED, struct cmdarg **args)
{
  struct sbuf *buf;
  if (current_window() != NULL)
    {
      rp_window *win = current_window();
      rp_window_elem *win_elem;
      win_elem = group_find_window (&rp_current_group->mapped_windows, win);
      if (!win_elem)
        win_elem = group_find_window (&rp_current_group->unmapped_windows, win);

      if (win_elem)
        {
          char *s;
          cmdret *ret;

          if (args[0] == NULL)
            s = defaults.info_fmt;
          else
            s = ARG_STRING(0);
          buf = sbuf_new (0);
          format_string (s, win_elem, buf);
          ret = cmdret_new (RET_SUCCESS, "%s", sbuf_get (buf));
          sbuf_free (buf);
          return ret;
        }
    }

  return cmdret_new (RET_SUCCESS, "No window.");
}
