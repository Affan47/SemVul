write_tickets_handler(const String &in_s, Element *e, void *thunk, ErrorHandler *errh)
{
    StrideSched *ss = (StrideSched *)e;
    int port = (intptr_t)thunk;
    String s = cp_uncomment(in_s);
    int tickets;
    if (!cp_integer(s, &tickets))
	return errh->error("tickets value must be integer");
    else
	return ss->set_tickets(port, tickets, errh);
}
