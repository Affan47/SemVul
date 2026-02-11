remove_channel(struct Channel * channel) {

	TRACE(("enter remove_channel"))
	TRACE(("channel index is %d", channel->index))

	cbuf_free(channel->writebuf);
	channel->writebuf = NULL;

	if (channel->extrabuf) {
		cbuf_free(channel->extrabuf);
		channel->extrabuf = NULL;
	}


	TRACE(("CLOSE writefd %d", channel->writefd))
	close(channel->writefd);
	TRACE(("CLOSE readfd %d", channel->readfd))
	close(channel->readfd);
	TRACE(("CLOSE errfd %d", channel->errfd))
	close(channel->errfd);

	channel->typedata = NULL;

	delete_channel(channel);

	TRACE(("leave remove_channel"))
}
