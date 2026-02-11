Ppollfdevents(void) {
  int events;
  if (Pstring_maybe("0")) return 0;
  events= 0;
  if (Pstring_maybe("POLLIN")) {
    events |= POLLIN;
    if (!Pstring_maybe("|")) return events;
  }
  if (Pstring_maybe("POLLOUT")) {
    events |= POLLOUT;
    if (!Pstring_maybe("|")) return events;
  }
  Pstring("POLLPRI","pollfdevents PRI?");
  return events;
}
