gdict_defbox_iter_backward_search (const GtkTextIter   *iter,
                                   const gchar         *str,
                                   GtkTextIter         *match_start,
                                   GtkTextIter         *match_end,
                                   const GtkTextIter   *limit)
{
  gchar **lines = NULL;
  GtkTextIter match;
  gboolean retval = FALSE;
  GtkTextIter search;

  g_return_val_if_fail (iter != NULL, FALSE);
  g_return_val_if_fail (str != NULL, FALSE);

  if (limit && gtk_text_iter_compare (iter, limit) <= 0)
    return FALSE;

  if (*str == '\0')
    {

      match = *iter;

      if (gtk_text_iter_backward_char (&match))
        {
          if (limit && gtk_text_iter_equal (&match, limit))
            return FALSE;

          if (match_start)
            *match_start = match;

          if (match_end)
            *match_end = match;

          return TRUE;
        }
      else
        return FALSE;
    }


  lines = breakup_string (str, "\n", -1);

  search = *iter;


  while (TRUE)
    {
      GtkTextIter end;
      gboolean res;

      if (limit && gtk_text_iter_compare (&search, limit) <= 0)
        break;

      res = backward_lines_match (&search, (const gchar**)lines,
                                  TRUE, FALSE,
                                  &match, &end);
      if (res)
        {
           if (limit == NULL ||
               (limit && gtk_text_iter_compare (&end, limit) > 0))
             {
               retval = TRUE;

               if (match_start)
                 *match_start = match;

               if (match_end)
                 *match_end = end;

             }

           break;
        }

      if (gtk_text_iter_get_line_offset (&search) == 0)
        {
          if (!gtk_text_iter_backward_line (&search))
            break;
        }
      else
        gtk_text_iter_set_line_offset (&search, 0);
    }

  g_strfreev ((gchar**) lines);

  return retval;
}
