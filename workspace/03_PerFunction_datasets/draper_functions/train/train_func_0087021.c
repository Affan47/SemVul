end_element_glade2 (struct element_state *p, const char *name)
{
  lex_pos_ty pos;
  char *msgid = NULL;
  char *msgctxt = NULL;

  pos.file_name = logical_file_name;
  pos.line_number = p->lineno;

  if (p->extract_context)
    {
      char *separator = strchr (p->buffer, '|');

      if (separator == NULL)
        {
          error_with_progname = false;
          error_at_line (0, 0,
                         pos.file_name,
                         pos.line_number,
                         _("\
Missing context for the string extracted from '%s' element"),
                         name);
          error_with_progname = true;
        }
      else
        {
          *separator = '\0';
          msgid = xstrdup (separator + 1);
          msgctxt = xstrdup (p->buffer);
        }
    }
  else
    {
      msgid = p->buffer;
      p->buffer = NULL;
    }

  if (msgid != NULL)
    remember_a_message (mlp, msgctxt, msgid,
                        null_context, &pos,
                        p->extracted_comment, savable_comment);
}
