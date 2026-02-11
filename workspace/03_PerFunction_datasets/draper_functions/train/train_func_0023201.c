ohfa (int *r)
{
  GtkTextIter start, end;
  char *txtmp, buff[3], *local_str;
  double c, i;
  int mem = 2;


  gtk_text_buffer_get_start_iter (textview->buffer, &start);
  gtk_text_buffer_get_end_iter (textview->buffer, &end);


  txtmp = gtk_text_buffer_get_text (textview->buffer, &start, &end, TRUE);

  i = strlen (txtmp);

  local_str = (char *) malloc (mem);


  for (c = *r = 0; c < i;)
    {
      if (txtmp[0] == ' ' || txtmp[0] == '\n')
        {
          txtmp++;
          c++;
          continue;
        }

      buff[0] = txtmp[0];
      buff[1] = txtmp[1];

      local_str[mem - 2] = strtol (buff, NULL, 16);
      local_str = (char *) realloc (local_str, mem++);

      txtmp += 2;
      c += 2;
      (*r)++;
    }
  local_str[mem - 2] = 0x00;

  return local_str;
}
