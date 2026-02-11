event_set_init_scalable (int *maxevents, unsigned int flags)
{
  struct event_set *ret = NULL;
#if EPOLL
  ret = ep_init (maxevents, flags);
  if (!ret)
    {
      msg (M_WARN, "Note: sys_epoll API is unavailable, falling back to poll/select API");
      ret = event_set_init_simple (maxevents, flags);
    }
#else
  ret = event_set_init_simple (maxevents, flags);
#endif
  ASSERT (ret);
  return ret;
}
