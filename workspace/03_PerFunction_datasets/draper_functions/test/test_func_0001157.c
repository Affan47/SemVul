Write(socket_queue* sock)
{

	int RetCode;
	static buffer *buf = NULL;
	char          *Ptr;

	if (sock->descriptor  < 0)
	{
#ifdef DEBUG
	syslog(LOG_DEBUG,"Write: Invalid Descriptor %d",sock->descriptor);
#endif
		return 1;
	}

	if (!buf)
	{
		buf = (buffer*) calloc(1,sizeof(buffer));

		if (!buf)
			return NO_MEMORY;

		if ((RetCode = initbuf(buf)) != 0)
			return RetCode;
	}

	if ((Ptr = itos(sock->msgbuf.used+_MSG_LEN+_MSG_MSG,_MSG_LEN)) == NULL)
		return -1;

	memcpy(buf->buf,Ptr,_MSG_LEN);
	buf->used = _MSG_LEN;

	if ((Ptr = itos(sock->msg,_MSG_MSG)) == NULL)
		return -1;

#ifdef DEBUG
	syslog(LOG_DEBUG,"Write: Message %d:*%s*",sock->msg,sock->msgbuf.buf);
#endif
	sock->msg = NO_MSG;

	memcpy(buf->buf+_MSG_LEN,Ptr,_MSG_MSG);
	buf->used += _MSG_MSG;

	if ((RetCode = bufcat(buf,&(sock->msgbuf),0,sock->msgbuf.used)) != 0)
		return RetCode;

	return write(sock->descriptor,buf->buf,buf->used);
}
