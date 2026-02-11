GNUNET_PEERINFO_notify_cancel (struct GNUNET_PEERINFO_NotifyContext *nc)
{
  if (NULL != nc->init)
  {
    GNUNET_CLIENT_notify_transmit_ready_cancel (nc->init);
    nc->init = NULL;
  }
  if (NULL != nc->client)
    GNUNET_CLIENT_disconnect (nc->client);
  if (GNUNET_SCHEDULER_NO_TASK != nc->task)
    GNUNET_SCHEDULER_cancel (nc->task);
  GNUNET_free (nc);
}
