send_msg_channel_data(struct Channel *channel, int isextended) {

	int len;
	size_t maxlen, size_pos;
	int fd;

	CHECKCLEARTOWRITE();

	TRACE(("enter send_msg_channel_data"))
	dropbear_assert(!channel->sent_close);

	if (isextended) {
		fd = channel->errfd;
	} else {
		fd = channel->readfd;
	}
	TRACE(("enter send_msg_channel_data isextended %d fd %d", isextended, fd))
	dropbear_assert(fd >= 0);

	maxlen = MIN(channel->transwindow, channel->transmaxpacket);


	maxlen = MIN(maxlen,
			ses.writepayload->size - 1 - 4 - 4 - (isextended ? 4 : 0));
	TRACE(("maxlen %d", maxlen))
	if (maxlen == 0) {
		TRACE(("leave send_msg_channel_data: no window"))
		return;
	}

	buf_putbyte(ses.writepayload,
			isextended ? SSH_MSG_CHANNEL_EXTENDED_DATA : SSH_MSG_CHANNEL_DATA);
	buf_putint(ses.writepayload, channel->remotechan);
	if (isextended) {
		buf_putint(ses.writepayload, SSH_EXTENDED_DATA_STDERR);
	}

	size_pos = ses.writepayload->pos;
	buf_putint(ses.writepayload, 0);


	len = read(fd, buf_getwriteptr(ses.writepayload, maxlen), maxlen);
	if (len <= 0) {
		if (len == 0 || errno != EINTR) {


			close_chan_fd(channel, fd, SHUT_RD);
		}
		ses.writepayload->len = ses.writepayload->pos = 0;
		TRACE(("leave send_msg_channel_data: len %d read err %d or EOF for fd %d",
					len, errno, fd))
		return;
	}
	buf_incrwritepos(ses.writepayload, len);

	buf_setpos(ses.writepayload, size_pos);
	buf_putint(ses.writepayload, len);

	channel->transwindow -= len;

	encrypt_packet();


	if (channel->flushing && len < (ssize_t)maxlen)
	{
		TRACE(("closing from channel, flushing out."))
		close_chan_fd(channel, fd, SHUT_RD);
	}
	TRACE(("leave send_msg_channel_data"))
}
