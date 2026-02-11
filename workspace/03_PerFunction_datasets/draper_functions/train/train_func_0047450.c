mailpop3_noop(mailpop3 * f)
{
  char command[POP3_STRING_SIZE];
  char * response;
  int r;

  if (f->pop3_state != POP3_STATE_TRANSACTION)
    return MAILPOP3_ERROR_BAD_STATE;

  snprintf(command, POP3_STRING_SIZE, "NOOP\r\n");
  r = send_command(f, command);
  if (r == -1)
    return MAILPOP3_ERROR_STREAM;

  response = read_line(f);
  if (response == NULL)
    return MAILPOP3_ERROR_STREAM;
  parse_response(f, response);

  return MAILPOP3_NO_ERROR;
}
