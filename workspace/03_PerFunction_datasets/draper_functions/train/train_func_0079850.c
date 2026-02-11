read_uidl(mailpop3 * f, carray * msg_tab)
{
  unsigned int indx;
  struct mailpop3_msg_info * msg;
  char * line;

  while (1) {
    char * uidl;

    line = read_line(f);
    if (line == NULL)
      goto err;

    if (mailstream_is_end_multiline(line))
      break;

    indx = strtol(line, &line, 10);

    if (!parse_space(&line))
      continue;

    uidl = strdup(line);
    if (uidl == NULL)
      continue;

    if (indx > carray_count(msg_tab)) {
      free(uidl);
      continue;
    }

    msg = carray_get(msg_tab, indx - 1);
    if (msg == NULL) {
      free(uidl);
      continue;
    }

    msg->msg_uidl = uidl;
  }

  return MAILPOP3_NO_ERROR;

 err:
  return MAILPOP3_ERROR_STREAM;
}
