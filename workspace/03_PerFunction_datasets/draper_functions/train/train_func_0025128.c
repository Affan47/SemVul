pt3_stop_feed(struct dvb_demux_feed *feed)
{
	struct pt3_adapter *adap;

	adap = container_of(feed->demux, struct pt3_adapter, demux);

	adap->num_feeds--;
	if (adap->num_feeds > 0 || !adap->thread)
		return 0;
	adap->num_feeds = 0;

	return pt3_stop_streaming(adap);
}
