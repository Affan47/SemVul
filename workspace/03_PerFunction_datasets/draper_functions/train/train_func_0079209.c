s_check_text (const GList *obj_list, SYMCHECK *s_current)
{
  const GList *iter;
  OBJECT *o_current;
  gboolean overbar_started, escape, leave_parser;
  char *message;
  char *text_string, *ptr;
  gunichar current_char;

  for (iter = obj_list; iter != NULL; iter = g_list_next(iter)) {
    o_current = iter->data;

    if (o_current->type != OBJ_TEXT)
      continue;

    overbar_started = escape = leave_parser = FALSE;
    text_string = o_current->text->string;

    for (ptr = text_string;
         ptr != NULL && !leave_parser;
         ptr = g_utf8_find_next_char (ptr, NULL)) {

      current_char = g_utf8_get_char_validated (ptr, -1);


      switch (current_char) {
      case '\0':

        leave_parser = TRUE;
        break;
      case '\\':
        if (escape == TRUE) {
          escape = FALSE;
        } else {
          escape = TRUE;
        }
        break;
      case '_':
        if (escape == TRUE) {
          escape = FALSE;
          if (overbar_started == TRUE) {
            overbar_started = FALSE;
          } else {
            overbar_started = TRUE;
          }
        }
        break;
      default:
        if (escape == TRUE) {
          message = g_strdup_printf ("Found text with a '\\' in it: consider"
                                     " to escape it with '\\\\' [%s]\n",
                                     text_string);
          s_current->warning_messages = g_list_append(s_current->warning_messages,
                                                      message);
          s_current->warning_count++;
          escape = FALSE;
        }
      }
    }

    if (escape == TRUE) {
      message = g_strdup_printf ("Found text with a trailing '\': consider to "
                                 "escape it with '\\\\' [%s]\n",
                                 text_string);
      s_current->warning_messages = g_list_append(s_current->warning_messages,
                                                  message);
      s_current->warning_count++;
    }

    if (overbar_started == TRUE) {
      message = g_strdup_printf ("Found text with unbalanced overbar "
                                 "markers '\\_' in it' [%s]\n",
                                 text_string);
      s_current->warning_messages = g_list_append(s_current->warning_messages,
                                                  message);
      s_current->warning_count++;
    }
  }
}
