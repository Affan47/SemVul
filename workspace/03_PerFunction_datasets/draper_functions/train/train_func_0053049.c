reply_to_map_with_len(EventSelector *es,
			     int fd,
			     char const *msg,
			     int len)
{
    EventTcpState *e;
    e = EventTcp_WriteNetstring(es, fd, msg, len, sent_map_reply,
				Settings.clientTimeout, NULL);
    if (!e) {
	if (DOLOG) {
	    syslog(LOG_ERR, "reply_to_map: EventTcp_WriteBuf failed: %m");
	}
	close(fd);
    }
    return e;
}
