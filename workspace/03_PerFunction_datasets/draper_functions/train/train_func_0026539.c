onCTL (int op, int fd, struct epoll_event *event)
{
  if (really_verbose) {
    JTRACE ("RGARG: EPOLL CTL-ing.") ( id() ) ( fd ) ( op );
  }

  JASSERT ( ((op==EPOLL_CTL_MOD || op==EPOLL_CTL_ADD) && event != NULL ) || op==EPOLL_CTL_DEL) ( epollType() ) ( id() )
    .Text ( "Passing a NULL event! HUH!");

  struct epoll_event myEvent;
  _type = EPOLL_CTL;
  if (op == EPOLL_CTL_DEL)
  {
      _fdToEvent.erase(fd);
      return;
  }
  memcpy (&myEvent, event, sizeof myEvent);
  _fdToEvent[fd] = myEvent;
}
