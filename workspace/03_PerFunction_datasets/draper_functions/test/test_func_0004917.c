pseudo_device_read(GIOChannel *source, GIOCondition condition, gpointer data)
{
	LOG(LOG_DEBUG, "Enter");
	Channel* channel = (Channel*)data;
	if (condition == G_IO_IN)
	{
		unsigned char buf[4096];

		int len = read(channel->fd, buf + channel->remaining, sizeof(buf) - channel->remaining);
		if (!channel->opened)
		{
			LOG(LOG_WARNING, "Write to a channel which wasn't acked to be open.");
			write_frame(channel->id, NULL, 0, GSM0710_TYPE_SABM | GSM0710_PF);
			LOG(LOG_DEBUG, "Leave");
			return TRUE;
		}
		if (len >= 0)
		{
			LOG(LOG_DEBUG, "Data from channel %d, %d bytes", channel->id, len);
			if (channel->remaining > 0)
			{
				memcpy(buf, channel->tmp, channel->remaining);
				free(channel->tmp);
				channel->tmp = NULL;
			}
			if (len + channel->remaining > 0)
				channel->remaining = handle_channel_data(buf, len + channel->remaining, channel->id);

			if (channel->remaining > 0)
			{
				channel->tmp = malloc(channel->remaining);
				memcpy(channel->tmp, buf + sizeof(buf) - channel->remaining, channel->remaining);
			}
			LOG(LOG_DEBUG, "Leave");
			return TRUE;
		}

		logical_channel_close(channel);
	}
	else if (condition == G_IO_HUP)
	{
		logical_channel_close(channel);
	}
	LOG(LOG_DEBUG, "Leave");
	return FALSE;
}
