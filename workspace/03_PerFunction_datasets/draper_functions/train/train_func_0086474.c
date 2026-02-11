shutDescriptors(Slave *s)
{
    char buffer[512];
    int n;

    if (s->slaveStdin >= 0) {
	close(s->slaveStdin);
	s->slaveStdin = -1;
    }
    if (s->slaveStdout >= 0) {
	close(s->slaveStdout);
	s->slaveStdout = -1;
    }
    if (s->slaveStderr >= 0) {
	Event_DelHandler(s->es, s->errHandler);
	s->errHandler = NULL;

	while( (n=read(s->slaveStderr, buffer, sizeof(buffer)-1)) > 0) {
	    buffer[n] = 0;
	    if (buffer[n-1] == '\n') {
		buffer[n-1] = 0;
	    }
	    if (DOLOG) {
		syslog(LOG_INFO, "Slave %d stderr: %s", SLAVENO(s), buffer);
	    }
	}
	close(s->slaveStderr);
	s->slaveStderr = -1;
    }
    if (s->slaveStatusFD >= 0) {
	close(s->slaveStatusFD);
	Event_DelHandler(s->es, s->statusHandler);
	s->statusHandler = NULL;
	s->slaveStatusFD = -1;
    }

    if (s->termHandler) {
	Event_DelHandler(s->es, s->termHandler);
	s->termHandler = NULL;
    }

    if (s->event) {
	EventTcp_CancelPending(s->event);
	s->event = NULL;
    }

    if (s->clientFD >= 0) {
	close(s->clientFD);
	s->clientFD = -1;
    }
}
