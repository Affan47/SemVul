ngene_start_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	struct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	struct ngene_channel *chan = dvbdmx->priv;

	if (chan->users == 0) {
		if (!chan->dev->cmd_timeout_workaround || !chan->running)
			set_transfer(chan, 1);
	}

	return ++chan->users;
}
