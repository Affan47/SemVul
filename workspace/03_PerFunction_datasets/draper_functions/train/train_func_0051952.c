start_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	struct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	struct ddb_input *input = dvbdmx->priv;

	if (!input->users)
		ddb_input_start(input);

	return ++input->users;
}
