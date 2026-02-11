recv_msg_channel_open_failure() {

	struct Channel * channel;

	channel = getchannel();

	if (!channel->await_open) {
		dropbear_exit("unexpected channel reply");
	}
	channel->await_open = 0;

	remove_channel(channel);
}
