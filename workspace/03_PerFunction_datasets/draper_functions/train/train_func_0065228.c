smtp_enumerate_messages (smtp_session_t session,
			 smtp_enumerate_messagecb_t cb, void *arg)
{
  smtp_message_t message;

  SMTPAPI_CHECK_ARGS (session != NULL && cb != NULL, 0);

  for (message = session->messages; message != NULL; message = message->next)
    (*cb) (message, arg);
  return 1;
}
