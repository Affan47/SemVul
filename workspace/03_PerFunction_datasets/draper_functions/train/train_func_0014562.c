request_notifications (struct GNUNET_PEERINFO_NotifyContext *nc)
{
  GNUNET_assert (NULL == nc->init);
  nc->init =
      GNUNET_CLIENT_notify_transmit_ready (nc->client,
                                           sizeof (struct GNUNET_MessageHeader),
                                           GNUNET_TIME_UNIT_FOREVER_REL,
                                           GNUNET_YES, &transmit_notify_request,
                                           nc);
}
