net_closeall(void) {
  struct sockinfo *i;
  time_t until;
  int ns;

  debug("Shutting down all sockets");


  until = time(0) + NET_LINGER_TIME;


  i = sockets;
  while (i) {
    i->closed = 1;
    i->throtbytes = i->throtamt = i->throtperiod = 0;
    i->throtlast = 0;
    i->activity_func = 0;
    i->error_func = 0;
    i = i->next;
  }


  ns = -1;
  while (time(0) < until)
    if (!(ns = net_poll()))
      break;

  if (ns > 0) {
    debug("%d sockets didn't send their data in time");
  } else if (ns < 0) {
    debug("Unexpected error occurred, oh well");
  } else {
    debug("All sockets cleaned up");
  }

  return ns;
}
