mailpop3_quit(mailpop3 * f)
{
  char command[POP3_STRING_SIZE];
  char * response;
  int r;
  int res;

  if ((f->pop3_state != POP3_STATE_AUTHORIZATION)
      && (f->pop3_state != POP3_STATE_TRANSACTION)) {
    res = MAILPOP3_ERROR_BAD_STATE;
    goto close;
  }

  snprintf(command, POP3_STRING_SIZE, "QUIT\r\n");
  r = send_command(f, command);
  if (r == -1) {
    res = MAILPOP3_ERROR_STREAM;
    goto close;
  }

  response = read_line(f);
  if (response == NULL) {
    res = MAILPOP3_ERROR_STREAM;
    goto close;
  }
  if (parse_response(f, response) == RESPONSE_OK) {
		res = MAILPOP3_NO_ERROR;
	}
	else {
		res = MAILPOP3_ERROR_QUIT_FAILED;
	}

  res = MAILPOP3_NO_ERROR;

 close:
  if (f->pop3_state != POP3_STATE_DISCONNECTED)
    mailstream_close(f->pop3_stream);

  if (f->pop3_timestamp != NULL) {
    free(f->pop3_timestamp);
    f->pop3_timestamp = NULL;
  }

  f->pop3_stream = NULL;
  if (f->pop3_msg_tab != NULL) {
    mailpop3_msg_info_tab_free(f->pop3_msg_tab);
    f->pop3_msg_tab = NULL;
  }

  f->pop3_state = POP3_STATE_DISCONNECTED;

  return res;
}
