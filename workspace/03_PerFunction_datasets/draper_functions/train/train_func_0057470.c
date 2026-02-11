GNUNET_SCHEDULER_add_write_net (struct GNUNET_TIME_Relative delay,
                                struct GNUNET_NETWORK_Handle *wfd,
                                GNUNET_SCHEDULER_Task task, void *task_cls)
{
#if MINGW
  struct GNUNET_NETWORK_FDSet *ws;
  GNUNET_SCHEDULER_TaskIdentifier ret;

  GNUNET_assert (wfd != NULL);
  ws = GNUNET_NETWORK_fdset_create ();
  GNUNET_NETWORK_fdset_set (ws, wfd);
  ret =
    GNUNET_SCHEDULER_add_select (GNUNET_SCHEDULER_PRIORITY_DEFAULT,
				 delay, NULL, ws,
                                   task, task_cls);
  GNUNET_NETWORK_fdset_destroy (ws);
  return ret;
#else
  GNUNET_assert (GNUNET_NETWORK_get_fd (wfd) >= 0);
  return add_without_sets (delay,
			   GNUNET_SCHEDULER_PRIORITY_DEFAULT,
			   -1, GNUNET_NETWORK_get_fd (wfd), task,
                           task_cls);
#endif
}
