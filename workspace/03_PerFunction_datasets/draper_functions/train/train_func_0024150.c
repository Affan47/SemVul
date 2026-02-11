jeex_get_current_byte_iter (GtkTextIter * start, GtkTextIter * end)
{
  char *str;

  end = gtk_text_iter_copy (start);

  if (!gtk_text_iter_is_end (start))
    {
      gtk_text_iter_forward_chars (end, 2);

      str = jeex_get_text (start, end);

      if (str[0] == 0x20 && str[1] == 0x20)
        {
          gtk_text_iter_backward_chars (end, 2);
          gtk_text_iter_backward_chars (start, 2);
        }

      while (str[0] == 0x20 || str[0] == 0x0A)
        {
          if (gtk_text_iter_is_end (end))
            {
              break;
            }
          gtk_text_iter_forward_char (start);
          gtk_text_iter_forward_char (end);
          g_free (str);
          str = jeex_get_text (start, end);
        }

      while (str[1] == 0x20 || str[1] == 0x0A)
        {
          if (gtk_text_iter_is_start (start))
            {
              break;
            }
          gtk_text_iter_backward_char (start);
          gtk_text_iter_backward_char (end);
          g_free (str);
          str = jeex_get_text (start, end);
        }

      if (*str != 0x20 && *str != 0x0A)
        {
          return str;
        }
    }

  gtk_text_iter_backward_chars (start, 2);
  str = jeex_get_text (start, end);
  while (*str == 0x20 || *str == 0x0A)
    {
      if (gtk_text_iter_is_start (start))
        {
          break;
        }
      gtk_text_iter_backward_char (start);
      gtk_text_iter_backward_char (end);
      g_free (str);
      str = jeex_get_text (start, end);
    }

  return str;
}
