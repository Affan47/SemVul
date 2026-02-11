mailsmtp_noop(mailsmtp * session)
{
  char command[SMTP_STRING_SIZE];
  int r;

  snprintf(command, SMTP_STRING_SIZE, "NOOP\r\n");
  r = send_command(session, command);
  if (r == -1)
    return MAILSMTP_ERROR_STREAM;
  r = read_response(session);
  if (r == 0)
    return MAILSMTP_ERROR_STREAM;

  return MAILSMTP_NO_ERROR;
}
