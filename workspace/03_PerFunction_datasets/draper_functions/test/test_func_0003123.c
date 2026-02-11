budget_stop_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux = feed->demux;
	struct av7110 *budget = demux->priv;
	int status;

	dprintk(2, "budget: %p\n", budget);

	spin_lock(&budget->feedlock1);
	status = stop_ts_capture(budget);
	spin_unlock(&budget->feedlock1);
	return status;
}
