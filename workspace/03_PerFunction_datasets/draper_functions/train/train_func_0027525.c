read_into(int fd) {
  char in_buf[BUF_S];
  char *passline;
  char *start, *end;
  int result;
  GtkWidget *output;
  GtkTextBuffer *outputbuf;
  GtkTextIter outputiter;

  if ((result = read(fd, in_buf, BUF_S - 1)) < 0) {
    g_warning("%s::%i: read returned negative!", __FILE__, __LINE__);
    return FALSE;
  } else if (result == 0) {
    return FALSE;
  } else {
    in_buf[result] = 0;
  }

  output = lookup_widget(GTK_WIDGET(wndMain), "txtOutput");
  outputbuf = gtk_text_view_get_buffer((GtkTextView *) output);

  gtk_text_buffer_get_iter_at_offset(outputbuf, &outputiter, -1);


  if ((passline = strstr(in_buf, "password: ")) == NULL) {
    gtk_text_buffer_insert(outputbuf, &outputiter, in_buf, result);
  } else {
    start = in_buf;
    end = in_buf;
    while ((end = (strchr(end + 1, '\n'))) < passline) {
      start = end;
    }

    if (start != in_buf) {
      gtk_text_buffer_insert(outputbuf, &outputiter, in_buf, (start - in_buf + 1));
    }
    gtk_text_buffer_insert_with_tags_by_name(outputbuf, &outputiter, start, (end - start + 1), "bold", NULL);

    if (end - in_buf - result > 0) {
      gtk_text_buffer_insert(outputbuf, &outputiter, end + 1, -1);
    }

  }


  if (strstr(in_buf, " finished at ") != NULL) {
    gtk_text_buffer_insert_with_tags_by_name(outputbuf, &outputiter, "<finished>\n\n", -1, "bold", NULL);
  }

  if (result == BUF_S - 1)
    return read_into(fd);
  else
    return TRUE;
}
