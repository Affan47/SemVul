ep_del (struct event_set *es, event_t event)
{
  struct epoll_event ev;
  struct ep_set *eps = (struct ep_set *) es;

  dmsg (D_EVENT_WAIT, "EP_DEL ev=%d", (int)event);

  ASSERT (!eps->fast);
  CLEAR (ev);
  epoll_ctl (eps->epfd, EPOLL_CTL_DEL, event, &ev);
}
