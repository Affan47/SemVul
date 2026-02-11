smtp_deliverby_set_mode (smtp_message_t message,
			 long time, enum by_mode mode, int trace)
{
  SMTPAPI_CHECK_ARGS (message != NULL, 0);
  SMTPAPI_CHECK_ARGS ((-999999999 <= time && time <= +999999999), 0);
  SMTPAPI_CHECK_ARGS (!(mode == By_RETURN && time <= 0), 0);

  message->by_time = time;
  message->by_mode = mode;
  message->by_trace = !!trace;
  return 1;
}
