read_response(mailsmtp * session)
{
  char * line;
  int code;

  mmap_string_assign(session->response_buffer, "");

  do {
    line = read_line(session);

    if (line != NULL) {
	code = parse_response(session, line);
        mmap_string_append_c(session->response_buffer, '\n');
      }
    else
      code = 0;
  }
  while ((code & SMTP_STATUS_CONTINUE) != 0);

  session->response = session->response_buffer->str;
	session->response_code = code;

  return code;
}
