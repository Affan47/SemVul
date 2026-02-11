smtp_enumerate_recipients (smtp_message_t message,
			   smtp_enumerate_recipientcb_t cb, void *arg)
{
  smtp_recipient_t recipient;

  SMTPAPI_CHECK_ARGS (message != NULL, 0);

  for (recipient = message->recipients;
       recipient != NULL;
       recipient = recipient->next)
    (*cb) (recipient, recipient->mailbox, arg);
  return 1;
}
