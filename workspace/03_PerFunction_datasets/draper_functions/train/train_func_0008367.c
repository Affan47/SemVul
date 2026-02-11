dvbdmx_release_ts_feed(struct dmx_demux *dmx,
				  struct dmx_ts_feed *ts_feed)
{
	struct dvb_demux *demux = (struct dvb_demux *)dmx;
	struct dvb_demux_feed *feed = (struct dvb_demux_feed *)ts_feed;

	mutex_lock(&demux->mutex);

	if (feed->state == DMX_STATE_FREE) {
		mutex_unlock(&demux->mutex);
		return -EINVAL;
	}
#ifndef NOBUFS
	vfree(feed->buffer);
	feed->buffer = NULL;
#endif

	feed->state = DMX_STATE_FREE;
	feed->filter->state = DMX_STATE_FREE;

	dvb_demux_feed_del(feed);

	feed->pid = 0xffff;

	if (feed->ts_type & TS_DECODER && feed->pes_type < DMX_PES_OTHER)
		demux->pesfilter[feed->pes_type] = NULL;

	mutex_unlock(&demux->mutex);
	return 0;
}
