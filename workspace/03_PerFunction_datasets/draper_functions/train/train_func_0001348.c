parse_greeting(mailimap * session,
	 			struct mailimap_greeting ** result)
{
  size_t indx;
  struct mailimap_greeting * greeting;
  int r;

  indx = 0;

  session->imap_response = NULL;

  r = mailimap_greeting_parse(session->imap_stream,
      session->imap_stream_buffer,
      &indx, &greeting, session->imap_progr_rate,
      session->imap_progr_fun);
  if (r != MAILIMAP_NO_ERROR)
    return r;

#if 0
  mailimap_greeting_print(greeting);
#endif

  greeting_store(session, greeting);

  if (greeting->gr_type == MAILIMAP_GREETING_RESP_COND_BYE) {
    if (greeting->gr_data.gr_bye->rsp_text->rsp_text != NULL) {
      if (mmap_string_assign(session->imap_response_buffer,
              greeting->gr_data.gr_bye->rsp_text->rsp_text) == NULL)
        return MAILIMAP_ERROR_MEMORY;
    }

    session->imap_response = session->imap_response_buffer->str;

    return MAILIMAP_ERROR_DONT_ACCEPT_CONNECTION;
  }

  if (greeting->gr_data.gr_auth->rsp_text->rsp_text != NULL) {
    if (mmap_string_assign(session->imap_response_buffer,
            greeting->gr_data.gr_auth->rsp_text->rsp_text) == NULL)
      return MAILIMAP_ERROR_MEMORY;
  }

  session->imap_response = session->imap_response_buffer->str;

  * result = greeting;

  return MAILIMAP_NO_ERROR;
}
