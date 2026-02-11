il_dbgfs_stations_read(struct file *file, char __user *user_buf, size_t count,
		       loff_t *ppos)
{
	struct il_priv *il = file->private_data;
	struct il_station_entry *station;
	int max_sta = il->hw_params.max_stations;
	char *buf;
	int i, j, pos = 0;
	ssize_t ret;

	const size_t bufsz = 30 + sizeof(char) * 500 * (il->num_stations);

	buf = kmalloc(bufsz, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	pos +=
	    scnprintf(buf + pos, bufsz - pos, "num of stations: %d\n\n",
		      il->num_stations);

	for (i = 0; i < max_sta; i++) {
		station = &il->stations[i];
		if (!station->used)
			continue;
		pos +=
		    scnprintf(buf + pos, bufsz - pos,
			      "station %d - addr: %pM, flags: %#x\n", i,
			      station->sta.sta.addr,
			      station->sta.station_flags_msk);
		pos +=
		    scnprintf(buf + pos, bufsz - pos,
			      "TID\tseq_num\ttxq_id\tframes\ttfds\t");
		pos +=
		    scnprintf(buf + pos, bufsz - pos,
			      "start_idx\tbitmap\t\t\trate_n_flags\n");

		for (j = 0; j < MAX_TID_COUNT; j++) {
			pos +=
			    scnprintf(buf + pos, bufsz - pos,
				      "%d:\t%#x\t%#x\t%u\t%u\t%u\t\t%#.16llx\t%#x",
				      j, station->tid[j].seq_number,
				      station->tid[j].agg.txq_id,
				      station->tid[j].agg.frame_count,
				      station->tid[j].tfds_in_queue,
				      station->tid[j].agg.start_idx,
				      station->tid[j].agg.bitmap,
				      station->tid[j].agg.rate_n_flags);

			if (station->tid[j].agg.wait_for_ba)
				pos +=
				    scnprintf(buf + pos, bufsz - pos,
					      " - waitforba");
			pos += scnprintf(buf + pos, bufsz - pos, "\n");
		}

		pos += scnprintf(buf + pos, bufsz - pos, "\n");
	}

	ret = simple_read_from_buffer(user_buf, count, ppos, buf, pos);
	kfree(buf);
	return ret;
}
