cb_note_close_timer(void *data)
{
  Timer_Data *td = data;

  if (!e_notification_closed_get(td->n))
    daemon_note_close(td->d, td->n, E_NOTIFICATION_CLOSED_EXPIRED);

  e_notification_unref(td->n);
  free(td);

  return ECORE_CALLBACK_CANCEL;
}
