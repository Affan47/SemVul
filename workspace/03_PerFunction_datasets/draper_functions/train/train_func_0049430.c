multichannel_stats_extended(struct multichannel *m,
			    struct nlif_handle *h, int fd)
{
	int i, active;

	for (i = 0; i < m->channel_num; i++) {
		if (m->current == m->channel[i]) {
			active = 1;
		} else {
			active = 0;
		}
		channel_stats_extended(m->channel[i], active, h, fd);
	}
}
