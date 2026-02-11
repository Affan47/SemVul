flexcop_pid_feed_control(struct flexcop_device *fc,
		struct dvb_demux_feed *dvbdmxfeed, int onoff)
{
	int max_pid_filter = 6;

	max_pid_filter -= 6 * fc->skip_6_hw_pid_filter;
	max_pid_filter += 32 * fc->has_32_hw_pid_filter;

	fc->feedcount += onoff ? 1 : -1;
	if (dvbdmxfeed->index >= max_pid_filter)
		fc->extra_feedcount += onoff ? 1 : -1;


	if (!fc->pid_filtering && fc->feedcount == onoff)
		flexcop_toggle_fullts_streaming(fc, onoff);

	if (fc->pid_filtering) {
		flexcop_pid_control \
			(fc, dvbdmxfeed->index, dvbdmxfeed->pid, onoff);

		if (fc->extra_feedcount > 0)
			flexcop_toggle_fullts_streaming(fc, 1);
		else if (dvbdmxfeed->pid == 0x2000)
			flexcop_toggle_fullts_streaming(fc, onoff);
		else
			flexcop_toggle_fullts_streaming(fc, 0);
	}


	if (fc->feedcount == onoff) {
		flexcop_rcv_data_ctrl(fc, onoff);
		if (fc->stream_control)
			fc->stream_control(fc, onoff);


		if (onoff == 0) {
			flexcop_reset_block_300(fc);
			flexcop_hw_filter_init(fc);
		}
	}
	return 0;
}
