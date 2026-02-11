client_delayed_retry (void *cls, const struct GNUNET_SCHEDULER_TaskContext *tc)
{
  struct GNUNET_CLIENT_TransmitHandle *th = cls;
  struct GNUNET_TIME_Relative delay;

  th->reconnect_task = GNUNET_SCHEDULER_NO_TASK;
  th->client->connection =
      do_connect (th->client->service_name, th->client->cfg, th->client->attempts++);
  if (NULL == th->client->connection)
  {

    delay =
        GNUNET_TIME_relative_min (GNUNET_TIME_absolute_get_remaining
                                  (th->timeout), th->client->back_off);
    th->client->back_off =
        GNUNET_TIME_relative_min (GNUNET_TIME_relative_multiply
                                  (th->client->back_off, 2),
                                  GNUNET_TIME_UNIT_SECONDS);
    LOG (GNUNET_ERROR_TYPE_DEBUG,
         "Transmission failed %u times, trying again in %llums.\n",
         MAX_ATTEMPTS - th->attempts_left,
         (unsigned long long) delay.rel_value);
    th->reconnect_task =
        GNUNET_SCHEDULER_add_delayed (delay, &client_delayed_retry, th);
    return;
  }
  th->th =
      GNUNET_CONNECTION_notify_transmit_ready (th->client->connection, th->size,
                                               GNUNET_TIME_absolute_get_remaining
                                               (th->timeout), &client_notify,
                                               th);
  if (NULL == th->th)
  {
    GNUNET_break (0);
    th->client->th = NULL;
    th->notify (th->notify_cls, 0, NULL);
    GNUNET_free (th);
    return;
  }
}
