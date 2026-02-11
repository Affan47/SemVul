handle_notify_input(EventSelector *es, int fd, char *buf,
		    int len, int flag, void *data)
{
    Listener *l = (Listener *) data;
    char *s;

    l->read_ev = NULL;
    if (flag == EVENT_TCP_FLAG_TIMEOUT || flag == EVENT_TCP_FLAG_IOERROR) {
	close_listener(l);
	return;
    }


    if (!len) {
	close_listener(l);
	return;
    }


    buf[len-1] = 0;
    len--;


    if (buf[0] != '?') {
	setup_read_event(l, es);
	return;
    }

    memset(l->msg_types, 0, NUM_MSG_TYPES);

    s = buf+1;
    while(*s) {
	if (*s >= 'A' && *s <= 'Z') {
	    l->msg_types[(*s) - 'A'] = 1;
	}
	if (*s == '*') {
	    memset(l->msg_types, 1, NUM_MSG_TYPES);
	}
	s++;
    }
    setup_read_event(l, es);
}
