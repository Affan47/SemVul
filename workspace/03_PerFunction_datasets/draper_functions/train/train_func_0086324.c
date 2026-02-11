handleSlaveStatusFD(EventSelector *es,
		    int fd,
		    unsigned int flags,
		    void *data)
{
    Slave *s = (Slave *) data;
    char buffer[512];
    int n;
    int changed = 0;

    while ( (n=read(fd, buffer, sizeof(buffer)-1)) > 0) {
	buffer[n] = 0;
	if (buffer[n-1] == '\n') {
	    buffer[n-1] = 0;
	}
	if (update_slave_status(s, buffer)) {
	    changed = 1;
	}
    }
    if (n == 0 || (n < 0 && errno != EAGAIN)) {

	if (n < 0) {
	    if (DOLOG) {
		syslog(LOG_WARNING,
		       "handleSlaveStatusFD: Error reading from slave %d's status pipe: %m", SLAVENO(s));
	    }
	}
	close(s->slaveStatusFD);
	Event_DelHandler(s->es, s->statusHandler);
	s->statusHandler = NULL;
	s->slaveStatusFD = -1;
    }
    if (changed) {
	notify_slave_status(s->es, SLAVENO(s), s->status_tag);
    }
}
