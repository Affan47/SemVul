modestack_finalize_channel(channel_t *channel)
{
	user_t *u;

	if (channel == modestackdata.channel)
	{
		if (modestackdata.modes_off & ircd->perm_mode)
		{

			slog(LG_DEBUG, "modestack_finalize_channel(): flushing modes for %s to clear perm mode", channel->name);
			u = user_find_named(modestackdata.source);
			if (u != NULL)
				join_sts(channel, u, false, channel_modes(channel, true));
			modestack_flush(&modestackdata);
			if (u != NULL)
				part_sts(channel, u);
		}
		else
			modestack_clear(&modestackdata);
	}
}
