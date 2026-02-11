WriteSMS (gn_sms *sms)
{
  gn_error error;
  PhoneEvent *e = (PhoneEvent *) g_malloc (sizeof (PhoneEvent));
  D_SMSMessage *m = (D_SMSMessage *) g_malloc (sizeof (D_SMSMessage));

  m->sms = sms;
  e->event = Event_SendSMSMessage;
  e->data = m;
  InsertEvent (e);
  pthread_mutex_lock (&sendSMSMutex);
  pthread_cond_wait (&sendSMSCond, &sendSMSMutex);
  pthread_mutex_unlock (&sendSMSMutex);

  gn_log_xdebug ("Address: %s\nText: %s\n", sms->remote.number, sms->user_data[0].u.text);

  error = m->status;
  g_free (m);

  if (error)
  {
    gn_log_xdebug ("Sending to %s unsuccessful. Error: %s\n", sms->remote.number, gn_error_print(error));
    if (smsdConfig.logFile)
      LogFile (_("Sending to %s unsuccessful. Error: %s\n"), sms->remote.number, gn_error_print(error));
  }
   else
  {
    gn_log_xdebug ("Sending to %s successful.\n", sms->remote.number);
    if (smsdConfig.logFile)
      LogFile (_("Sending to %s successful.\n"), sms->remote.number);
  }

  return (error);
}
