sequence_timeout_callback (void *user_data)
{
  WnckTasklist *tasklist = user_data;
  GList *tmp;
  GTimeVal now;
  long tv_sec, tv_usec;
  double elapsed;

  g_get_current_time (&now);

 restart:
  tmp = tasklist->priv->startup_sequences;
  while (tmp != NULL)
    {
      WnckTask *task = WNCK_TASK (tmp->data);

      sn_startup_sequence_get_last_active_time (task->startup_sequence,
                                                &tv_sec, &tv_usec);

      elapsed =
        ((((double)now.tv_sec - tv_sec) * G_USEC_PER_SEC +
          (now.tv_usec - tv_usec))) / 1000.0;

      if (elapsed > STARTUP_TIMEOUT)
        {
          g_assert (task->button != NULL);

          gtk_widget_destroy (task->button);

          goto restart;


        }

      tmp = tmp->next;
    }

  if (tasklist->priv->startup_sequences == NULL)
    {
      tasklist->priv->startup_sequence_timeout = 0;
      return FALSE;
    }
  else
    return TRUE;
}
