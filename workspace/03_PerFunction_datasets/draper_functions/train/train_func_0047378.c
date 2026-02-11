rl_tilde_expand (ignore, key)
     int ignore, key;
{
  register int start, end;
  char *homedir, *temp;
  int len;

  end = rl_point;
  start = end - 1;

  if (rl_point == rl_end && rl_line_buffer[rl_point] == '~')
    {
      homedir = tilde_expand ("~");
      _rl_replace_text (homedir, start, end);
      xfree (homedir);
      return (0);
    }
  else if (rl_line_buffer[start] != '~')
    {
      for (; !whitespace (rl_line_buffer[start]) && start >= 0; start--)
        ;
      start++;
    }

  end = start;
  do
    end++;
  while (whitespace (rl_line_buffer[end]) == 0 && end < rl_end);

  if (whitespace (rl_line_buffer[end]) || end >= rl_end)
    end--;


  if (rl_line_buffer[start] == '~')
    {
      len = end - start + 1;
      temp = (char *)xmalloc (len + 1);
      strncpy (temp, rl_line_buffer + start, len);
      temp[len] = '\0';
      homedir = tilde_expand (temp);
      xfree (temp);

      _rl_replace_text (homedir, start, end);
      xfree (homedir);
    }

  return (0);
}
